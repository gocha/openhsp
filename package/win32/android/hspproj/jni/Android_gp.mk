LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := hsp3gptest4
LOCAL_CFLAGS := -D__ANDROID__ -Wno-narrowing -DHSPNDK -DHSPEMBED -DHSPDISH -DHSPDISHGP
LOCAL_CPPFLAGS  += -fexceptions -std=c++11 -frtti -Wno-switch-enum -Wno-switch -Wno-narrowing
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES += ../hsplib36r1
LOCAL_C_INCLUDES += ../gameplay/src
LOCAL_C_INCLUDES += ../extlib/src

LOCAL_SRC_FILES := hsp3embed/hsp3r.cpp hsp3embed/hspsource.cpp javafunc.cpp maingp.cpp \
PlatformAndroid.cpp \
../../hsplib36r1/hsp_native_app_glue.c \
../../hsplib36r1/hsp3embed/hsp3code.cpp \
../../hsplib36r1/hsp3embed/hsp3embed.cpp \
../../hsplib36r1/hsp3embed/hspvar_util.cpp \
../../hsplib36r1/hsp3embed/misc.cpp \
../../hsplib36r1/hsp3/dpmread.cpp \
../../hsplib36r1/hsp3/essprite.cpp \
../../hsplib36r1/hsp3/geometry.cpp \
../../hsplib36r1/hsp3/hsp3debug.cpp \
../../hsplib36r1/hsp3/hsp3gr_dish.cpp \
../../hsplib36r1/hsp3/hsp3int.cpp \
../../hsplib36r1/hsp3/hspvar_core.cpp \
../../hsplib36r1/hsp3/hspvar_double.cpp \
../../hsplib36r1/hsp3/hspvar_int.cpp \
../../hsplib36r1/hsp3/hspvar_label.cpp \
../../hsplib36r1/hsp3/hspvar_str.cpp \
../../hsplib36r1/hsp3/hspvar_struct.cpp \
../../hsplib36r1/hsp3/hspwnd_dish.cpp \
../../hsplib36r1/hsp3/hspwnd_obj.cpp \
../../hsplib36r1/hsp3/hspwnd_edit.cpp \
../../hsplib36r1/hsp3/random.cpp \
../../hsplib36r1/hsp3/stack.cpp \
../../hsplib36r1/hsp3/strbuf.cpp \
../../hsplib36r1/hsp3/strnote.cpp \
../../hsplib36r1/hsp3/sysreq.cpp \
../../hsplib36r1/hsp3/texmes.cpp \
../../hsplib36r1/hsp3/ndk/fontsystem.cpp \
../../hsplib36r1/hsp3/ndk/supio_ndk.cpp \
../../hsplib36r1/hsp3/ndk/hsp3ext_ndk.cpp \
../../hsplib36r1/hsp3/ndk/mmman.cpp \
../../hsplib36r1/hsp3/ndk/webtask_ndk.cpp \
../../hsplib36r1/hsp3/ndkgp/hgiox.cpp \
../../hsplib36r1/hsp3/ndkgp/gamehsp.cpp \
../../hsplib36r1/hsp3/ndkgp/gpcam.cpp \
../../hsplib36r1/hsp3/ndkgp/gplgt.cpp \
../../hsplib36r1/hsp3/ndkgp/gpmat.cpp \
../../hsplib36r1/hsp3/ndkgp/gpphy.cpp \
../../hsplib36r1/hsp3/ndkgp/gpevent.cpp \
../../gameplay/src/AbsoluteLayout.cpp \
../../gameplay/src/AIAgent.cpp \
../../gameplay/src/AIController.cpp \
../../gameplay/src/AIMessage.cpp \
../../gameplay/src/AIState.cpp \
../../gameplay/src/AIStateMachine.cpp \
../../gameplay/src/Animation.cpp \
../../gameplay/src/AnimationClip.cpp \
../../gameplay/src/AnimationController.cpp \
../../gameplay/src/AnimationTarget.cpp \
../../gameplay/src/AnimationValue.cpp \
../../gameplay/src/AudioController.cpp \
../../gameplay/src/AudioListener.cpp \
../../gameplay/src/AudioSource.cpp \
../../gameplay/src/BoundingBox.cpp \
../../gameplay/src/BoundingSphere.cpp \
../../gameplay/src/Bundle.cpp \
../../gameplay/src/Button.cpp \
../../gameplay/src/Camera.cpp \
../../gameplay/src/CheckBox.cpp \
../../gameplay/src/Container.cpp \
../../gameplay/src/Control.cpp \
../../gameplay/src/ControlFactory.cpp \
../../gameplay/src/Curve.cpp \
../../gameplay/src/DebugNew.cpp \
../../gameplay/src/DepthStencilTarget.cpp \
../../gameplay/src/Drawable.cpp \
../../gameplay/src/Effect.cpp \
../../gameplay/src/FileSystem.cpp \
../../gameplay/src/FlowLayout.cpp \
../../gameplay/src/Font.cpp \
../../gameplay/src/Form.cpp \
../../gameplay/src/FrameBuffer.cpp \
../../gameplay/src/Frustum.cpp \
../../gameplay/src/Game.cpp \
../../gameplay/src/Gamepad.cpp \
../../gameplay/src/HeightField.cpp \
../../gameplay/src/Image.cpp \
../../gameplay/src/ImageControl.cpp \
../../gameplay/src/Joint.cpp \
../../gameplay/src/JoystickControl.cpp \
../../gameplay/src/Label.cpp \
../../gameplay/src/Layout.cpp \
../../gameplay/src/Light.cpp \
../../gameplay/src/Logger.cpp \
../../gameplay/src/Material.cpp \
../../gameplay/src/MaterialParameter.cpp \
../../gameplay/src/MathUtil.cpp \
../../gameplay/src/Matrix.cpp \
../../gameplay/src/Mesh.cpp \
../../gameplay/src/MeshBatch.cpp \
../../gameplay/src/MeshPart.cpp \
../../gameplay/src/MeshSkin.cpp \
../../gameplay/src/Model.cpp \
../../gameplay/src/Node.cpp \
../../gameplay/src/ParticleEmitter.cpp \
../../gameplay/src/Pass.cpp \
../../gameplay/src/PhysicsCharacter.cpp \
../../gameplay/src/PhysicsCollisionObject.cpp \
../../gameplay/src/PhysicsCollisionShape.cpp \
../../gameplay/src/PhysicsConstraint.cpp \
../../gameplay/src/PhysicsController.cpp \
../../gameplay/src/PhysicsFixedConstraint.cpp \
../../gameplay/src/PhysicsGenericConstraint.cpp \
../../gameplay/src/PhysicsGhostObject.cpp \
../../gameplay/src/PhysicsHingeConstraint.cpp \
../../gameplay/src/PhysicsRigidBody.cpp \
../../gameplay/src/PhysicsSocketConstraint.cpp \
../../gameplay/src/PhysicsSpringConstraint.cpp \
../../gameplay/src/PhysicsVehicle.cpp \
../../gameplay/src/PhysicsVehicleWheel.cpp \
../../gameplay/src/Plane.cpp \
../../gameplay/src/Platform.cpp \
../../gameplay/src/Properties.cpp \
../../gameplay/src/Quaternion.cpp \
../../gameplay/src/RadioButton.cpp \
../../gameplay/src/Ray.cpp \
../../gameplay/src/Rectangle.cpp \
../../gameplay/src/Ref.cpp \
../../gameplay/src/RenderState.cpp \
../../gameplay/src/RenderTarget.cpp \
../../gameplay/src/Scene.cpp \
../../gameplay/src/SceneLoader.cpp \
../../gameplay/src/ScreenDisplayer.cpp \
../../gameplay/src/ScriptController.cpp \
../../gameplay/src/ScriptTarget.cpp \
../../gameplay/src/Slider.cpp \
../../gameplay/src/Sprite.cpp \
../../gameplay/src/SpriteBatch.cpp \
../../gameplay/src/stb_image.cpp \
../../gameplay/src/Technique.cpp \
../../gameplay/src/Terrain.cpp \
../../gameplay/src/TerrainPatch.cpp \
../../gameplay/src/Text.cpp \
../../gameplay/src/TextBox.cpp \
../../gameplay/src/Texture.cpp \
../../gameplay/src/Theme.cpp \
../../gameplay/src/ThemeStyle.cpp \
../../gameplay/src/TileSet.cpp \
../../gameplay/src/Transform.cpp \
../../gameplay/src/Vector2.cpp \
../../gameplay/src/Vector3.cpp \
../../gameplay/src/Vector4.cpp \
../../gameplay/src/VertexAttributeBinding.cpp \
../../gameplay/src/VertexFormat.cpp \
../../gameplay/src/VerticalLayout.cpp \
../../extlib/src/BulletCollision/BroadphaseCollision/btAxisSweep3.cpp \
../../extlib/src/BulletCollision/BroadphaseCollision/btBroadphaseProxy.cpp \
../../extlib/src/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.cpp \
../../extlib/src/BulletCollision/BroadphaseCollision/btDbvt.cpp \
../../extlib/src/BulletCollision/BroadphaseCollision/btDbvtBroadphase.cpp \
../../extlib/src/BulletCollision/BroadphaseCollision/btDispatcher.cpp \
../../extlib/src/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.cpp \
../../extlib/src/BulletCollision/BroadphaseCollision/btOverlappingPairCache.cpp \
../../extlib/src/BulletCollision/BroadphaseCollision/btQuantizedBvh.cpp \
../../extlib/src/BulletCollision/BroadphaseCollision/btSimpleBroadphase.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btBoxBoxDetector.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btCollisionDispatcher.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btCollisionObject.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btCollisionWorld.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btCompoundCompoundCollisionAlgorithm.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btGhostObject.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btHashedSimplePairCache.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btInternalEdgeUtility.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btManifoldResult.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btSimulationIslandManager.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.cpp  \
../../extlib/src/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/btUnionFind.cpp \
../../extlib/src/BulletCollision/CollisionDispatch/SphereTriangleDetector.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btBox2dShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btBoxShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btCapsuleShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btCollisionShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btCompoundShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btConcaveShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btConeShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btConvex2dShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btConvexHullShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btConvexInternalShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btConvexPointCloudShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btConvexPolyhedron.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btConvexShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btCylinderShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btEmptyShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btMinkowskiSumShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btMultiSphereShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btOptimizedBvh.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btPolyhedralConvexShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btShapeHull.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btSphereShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btStaticPlaneShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btStridingMeshInterface.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btTetrahedronShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btTriangleBuffer.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btTriangleCallback.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btTriangleMesh.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btTriangleMeshShape.cpp \
../../extlib/src/BulletCollision/CollisionShapes/btUniformScalingShape.cpp \
../../extlib/src/BulletCollision/Gimpact/btContactProcessing.cpp \
../../extlib/src/BulletCollision/Gimpact/btGenericPoolAllocator.cpp \
../../extlib/src/BulletCollision/Gimpact/btGImpactBvh.cpp \
../../extlib/src/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.cpp \
../../extlib/src/BulletCollision/Gimpact/btGImpactQuantizedBvh.cpp \
../../extlib/src/BulletCollision/Gimpact/btGImpactShape.cpp \
../../extlib/src/BulletCollision/Gimpact/btTriangleShapeEx.cpp \
../../extlib/src/BulletCollision/Gimpact/gim_box_set.cpp \
../../extlib/src/BulletCollision/Gimpact/gim_contact.cpp \
../../extlib/src/BulletCollision/Gimpact/gim_memory.cpp \
../../extlib/src/BulletCollision/Gimpact/gim_tri_collision.cpp \
../../extlib/src/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.cpp \
../../extlib/src/BulletCollision/NarrowPhaseCollision/btConvexCast.cpp \
../../extlib/src/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.cpp \
../../extlib/src/BulletCollision/NarrowPhaseCollision/btGjkEpa2.cpp \
../../extlib/src/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.cpp \
../../extlib/src/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.cpp \
../../extlib/src/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.cpp \
../../extlib/src/BulletCollision/NarrowPhaseCollision/btPersistentManifold.cpp \
../../extlib/src/BulletCollision/NarrowPhaseCollision/btPolyhedralContactClipping.cpp \
../../extlib/src/BulletCollision/NarrowPhaseCollision/btRaycastCallback.cpp \
../../extlib/src/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.cpp \
../../extlib/src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.cpp \
../../extlib/src/BulletDynamics/Character/btKinematicCharacterController.cpp \
../../extlib/src/BulletDynamics/ConstraintSolver/btConeTwistConstraint.cpp \
../../extlib/src/BulletDynamics/ConstraintSolver/btContactConstraint.cpp \
../../extlib/src/BulletDynamics/ConstraintSolver/btFixedConstraint.cpp \
../../extlib/src/BulletDynamics/ConstraintSolver/btGearConstraint.cpp \
../../extlib/src/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.cpp \
../../extlib/src/BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.cpp \
../../extlib/src/BulletDynamics/ConstraintSolver/btHinge2Constraint.cpp \
../../extlib/src/BulletDynamics/ConstraintSolver/btHingeConstraint.cpp \
../../extlib/src/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.cpp \
../../extlib/src/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.cpp \
../../extlib/src/BulletDynamics/ConstraintSolver/btSliderConstraint.cpp \
../../extlib/src/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.cpp \
../../extlib/src/BulletDynamics/ConstraintSolver/btTypedConstraint.cpp \
../../extlib/src/BulletDynamics/ConstraintSolver/btUniversalConstraint.cpp \
../../extlib/src/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.cpp \
../../extlib/src/BulletDynamics/Dynamics/btRigidBody.cpp \
../../extlib/src/BulletDynamics/Dynamics/btSimpleDynamicsWorld.cpp \
../../extlib/src/BulletDynamics/Dynamics/Bullet-C-API.cpp \
../../extlib/src/BulletDynamics/Featherstone/btMultiBody.cpp \
../../extlib/src/BulletDynamics/Featherstone/btMultiBodyConstraint.cpp \
../../extlib/src/BulletDynamics/Featherstone/btMultiBodyConstraintSolver.cpp \
../../extlib/src/BulletDynamics/Featherstone/btMultiBodyDynamicsWorld.cpp \
../../extlib/src/BulletDynamics/Featherstone/btMultiBodyJointLimitConstraint.cpp \
../../extlib/src/BulletDynamics/Featherstone/btMultiBodyJointMotor.cpp \
../../extlib/src/BulletDynamics/Featherstone/btMultiBodyPoint2Point.cpp \
../../extlib/src/BulletDynamics/MLCPSolvers/btDantzigLCP.cpp \
../../extlib/src/BulletDynamics/MLCPSolvers/btMLCPSolver.cpp \
../../extlib/src/BulletDynamics/Vehicle/btRaycastVehicle.cpp \
../../extlib/src/BulletDynamics/Vehicle/btWheelInfo.cpp \
../../extlib/src/LinearMath/btAlignedAllocator.cpp \
../../extlib/src/LinearMath/btConvexHull.cpp \
../../extlib/src/LinearMath/btConvexHullComputer.cpp \
../../extlib/src/LinearMath/btGeometryUtil.cpp \
../../extlib/src/LinearMath/btPolarDecomposition.cpp \
../../extlib/src/LinearMath/btQuickprof.cpp \
../../extlib/src/LinearMath/btSerializer.cpp \
../../extlib/src/LinearMath/btVector3.cpp \
../../extlib/src/zlib/adler32.c \
../../extlib/src/zlib/compress.c \
../../extlib/src/zlib/crc32.c \
../../extlib/src/zlib/deflate.c \
../../extlib/src/zlib/gzclose.c \
../../extlib/src/zlib/gzlib.c \
../../extlib/src/zlib/gzread.c \
../../extlib/src/zlib/gzwrite.c \
../../extlib/src/zlib/inflate.c \
../../extlib/src/zlib/infback.c \
../../extlib/src/zlib/inftrees.c \
../../extlib/src/zlib/inffast.c \
../../extlib/src/zlib/trees.c \
../../extlib/src/zlib/uncompr.c \
../../extlib/src/zlib/zutil.c \
../../extlib/src/libpng/png.c \
../../extlib/src/libpng/pngerror.c \
../../extlib/src/libpng/pngget.c \
../../extlib/src/libpng/pngmem.c \
../../extlib/src/libpng/pngpread.c \
../../extlib/src/libpng/pngread.c \
../../extlib/src/libpng/pngrio.c \
../../extlib/src/libpng/pngrtran.c \
../../extlib/src/libpng/pngrutil.c \
../../extlib/src/libpng/pngset.c \
../../extlib/src/libpng/pngtrans.c \
../../extlib/src/libpng/pngwio.c \
../../extlib/src/libpng/pngwrite.c \
../../extlib/src/libpng/pngwtran.c \
../../extlib/src/libpng/pngwutil.c

LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -lOpenSLES -ljnigraphics -Llibs/$(TARGET_ARCH_ABI)

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
