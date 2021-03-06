#pragma once

#ifdef WIN32
#define OVR_OS_WIN32 //Doing this can be dangerous in a header file. The define will cause this definition to propagate to all users of this .h
#endif //WIN32

#include "AftrSDLIncludes.h"
#include "AftrOpenGLIncludes.h"
#include "OVR_CAPI_GL.h"

#include "AftrGLRendererBase.h"
#include "Vector.h"

namespace Aftr
{

class Texture;
class AftrFBOUserSpecifiedRenderTarget;
class IndexedGeometryQuad;
class WOGUI;
class ModelMeshSkin;
class GLSLShaderOVRBarrelDistortion;
struct OculusTextureBuffer;


class AftrGLRendererOVR : public AftrGLRendererBase
{
public:
   static AftrGLRendererOVR* New();
   virtual ~AftrGLRendererOVR();
   
   /**
      Invokes either renderSingular() (monoscopic camera using double buffering (one viewpoint)) or
      renderStereo() (stereoscopic camera using quad buffering (two viewpoints (right/left eyes))).
      After the above invocation completes, this method swaps the buffers displaying the
      newly generated frame to the screen.
   */
   virtual void render( Camera& cam, WorldContainer& wList );

   /**
      Called by render when rendering the world using stereoscopic mode (3D goggles).
      Computes asymmetric stereoscopic frustum.
      Invokes setUpStereoCamera() for right eye, calls renderScene() for right eye.
      Invokes setUpStereoCamera() for left eye, calls renderScene() for left eye.
   */
   virtual void renderStereo( Camera& cam, WorldContainer& wList ); ///< Invokes setUpStereoCamera then invokes renderScene twice, once for right eye, once for left

   /**
      Called by render when rendering the world in non-stereoscopic mode (no 3D goggles).
      Invokes setUpSingleCamera() and then invokes renderScene().
   */
   virtual void renderSingular( Camera& cam, WorldContainer& wList );
	
   /**
      Draws all WO* within the worldLst; typically called from 
      renderSingular() or renderStereo() or an FBO render.

      Draws all objects contained in wList from the perspective of cam. All objects are drawn into which
      ever buffer is currently bound. This could be the GL_BACK_BUFFER, a GL Texture bound via an FBO,
      or any other valid buffer object.
   */
   virtual void renderScene( const Camera& cam, WorldContainer& wList, bool clearColorDepthStencilBuffersPriorToRender = true );

   /**
     Renders for stereo modes that require each pair of frames to be spliced either vertically or horizontally.
     The oculus Rift requires a vertically split rendering to create a stereoscopic display
   */
   virtual void renderSplit( Camera& cam, WorldContainer& wList );

   /**
      Methods that perform selection. The scene is rendered via selection to identify a WO or point selected from a mouse click or other
      event.
   */
   //virtual void renderSelection( Camera& cam, WorldContainer& wList );
   virtual void renderSelection( Camera& cam, WorldContainer& wList, SelectionQueryResult& queryResult, unsigned int pixelX, unsigned int pixelY );
   virtual void renderSelectionSingular( Camera& cam, WorldContainer& wList );
   virtual void renderSelectionScene( const Camera& cam, WorldContainer& wList, bool clearColorDepthStencilBuffersPriorToRender = true );

   void postProcessFrame( Camera& cam, const ovrEyeRenderDesc eye[2] );

   ovrSession getSessionOVR() const noexcept { return this->session; }

   /**
      Generates 1 frame that contains the left eye image on the left half of the screen, and the right eye image on the right side of the screen.
   */
   //virtual void renderSplitVertically( Camera* cam );

   virtual void captureNextFrame( bool captureNextFrame ) { this->CaptureNextFrame = captureNextFrame; }
   virtual bool captureNextFrame() { return this->CaptureNextFrame; }

   virtual void captureNextFrameToFile( bool captureNextFrameToFile ) { this->CaptureNextFrame = captureNextFrameToFile; }
   virtual bool captureNextFrameToFile() { return this->CaptureNextFrame; }

   static std::string toStringOculusSessionInfo( const ovrSession& session );

   static Mat4 convertOculusSDKPoseToAftrMat4Pose( const ovrPosef& pose, bool includePositionIn4thColumn = true );

protected:
   AftrGLRendererOVR();
   virtual void onCreate();

   AftrFBOUserSpecifiedRenderTarget* stereoFBO = nullptr; ///< FBO Used to render the frame into frameTex
   Texture* frameTex = nullptr; ///< Texture holding the current frame that is rendered with post-processing barrel distortion.
   //IndexedGeometryQuad* stereoQuad; ///< Quad upon which frameTex is applied
   //ModelMeshSkin* skin; ///< Skin containing the shader that is applied onto stereoQuad, so the shader is applied to frameTex
   //GLSLShaderOVRBarrelDistortion* oculusBarrelDistorter; ///< Barrel Distortion shader to correct for the Oculus' pincushion effect

   float orthoProj[16];
   Vector woGUIRootStereoOffset;
   

   //New Oculus integration stuff
   ovrSession session = nullptr; ///< Session that ties a particular HMD/configuration with this renderer
   ovrGraphicsLuid luid; ///< Identifies the graphics card used to drive this HMD. Needs to be used when a machine has multiple graphics cards
   unsigned int frameIndex = 0; ///< Frame count used in conjunction with predictive timer
   bool notifyRiftToRemoveHealthAndWarningDisplay = true;
   std::array< std::unique_ptr<OculusTextureBuffer>, 2 > eyeRenderTexture = { nullptr,nullptr };
   ovrMirrorTexture mirrorTexture = nullptr;
   ovrSizei mirrorTextureSize = { 0, 0 };
   GLuint mirrorFBO = 0;

};

} //namespace Aftr
