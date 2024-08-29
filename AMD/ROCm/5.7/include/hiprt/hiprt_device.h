#pragma once

#define HIPRT_PUBLIC_DEVICE_H
#define HIPRT_DEVICE __device__

#include <hiprt/hiprt_common.h>
#include <hiprt/hiprt_types.h>
#include <hiprt/hiprt_vec.h>

/** \brief A stack using (slow) local memory internally.
 *
 */
class alignas( 32 ) hiprtPrivateStack
{
  public:
	static constexpr u32 StackSize = 64;
	HIPRT_DEVICE		 hiprtPrivateStack() : m_top( 0u ) {}

	HIPRT_DEVICE int  pop() { return m_stackBuffer[--m_top]; }
	HIPRT_DEVICE void push( int val ) { m_stackBuffer[m_top++] = val; }
	HIPRT_DEVICE bool empty() const { return m_top == 0u; }
	HIPRT_DEVICE int  vacancy() const { return StackSize - m_top; }
	HIPRT_DEVICE void reset() { m_top = 0u; }

  private:
	int m_stackBuffer[StackSize];
	u32 m_top;
};

/** \brief A stack using both (fast) shared memory and (slow) global memory.
 *
 * The stack uses shared memory if there is enough space.
 * Otherwise, it uses global memory as a backup.
 */
class alignas( 32 ) hiprtGlobalStack
{
  public:
	static constexpr u32 Stride	   = hiprt::WarpSize;
	static constexpr u32 LogStride = hiprt::Log2( Stride );

	HIPRT_DEVICE
	hiprtGlobalStack( hiprtGlobalStackBuffer globalStackBuffer, hiprtSharedStackBuffer sharedStackBuffer );

	HIPRT_DEVICE int pop();

	HIPRT_DEVICE void push( int val );

	HIPRT_DEVICE int vacancy() const;

	HIPRT_DEVICE bool empty() const;

	HIPRT_DEVICE void reset();

  private:
	int* m_globalStackBuffer;
	int* m_sharedStackBuffer;
	u32	 m_globalStackSize;
	u32	 m_sharedStackSize;
	int	 m_globalIndex;
	int	 m_sharedIndex;
	u32	 m_sharedCount;
};

/** \brief A stack using both (fast) shared memory and (slow) global memory with dynamic assignment.
 *
 * The stack uses shared memory if there is enough space.
 * Otherwise, it uses global memory as a backup.
 */
class alignas( 32 ) hiprtDynamicStack
{
  public:
	static constexpr u32 Stride	   = hiprt::WarpSize;
	static constexpr u32 LogStride = hiprt::Log2( Stride );

	HIPRT_DEVICE
	hiprtDynamicStack( hiprtGlobalStackBuffer globalStackBuffer, hiprtSharedStackBuffer sharedStackBuffer );

	HIPRT_DEVICE
	~hiprtDynamicStack();

	HIPRT_DEVICE int pop();

	HIPRT_DEVICE void push( int val );

	HIPRT_DEVICE int vacancy() const;

	HIPRT_DEVICE bool empty() const;

	HIPRT_DEVICE void reset();

  private:
	int* m_globalStackLock;
	int* m_globalStackBuffer;
	int* m_sharedStackBuffer;
	u32	 m_globalStackSize;
	u32	 m_sharedStackSize;
	int	 m_globalIndex;
	int	 m_sharedIndex;
	u32	 m_sharedCount;
};

/** \brief A traversal object for finding the closest hit with hiprtGeometry containing triangles.
 *
 * It uses a private stack with size 64 internally.
 */
template <hiprtPrimitiveNodeType PrimitiveNodeType, hiprtTraversalType TraversalType>
class hiprtGeomTraversal_impl;

class hiprtGeomTraversalClosest
{
  public:
	HIPRT_DEVICE hiprtGeomTraversalClosest(
		hiprtGeometry	   geom,
		const hiprtRay&	   ray,
		hiprtTraversalHint hint		 = hiprtTraversalHintDefault,
		void*			   payload	 = nullptr,
		hiprtFuncTable	   funcTable = nullptr,
		u32				   rayType	 = 0 );
	HIPRT_DEVICE hiprtHit			 getNextHit();
	HIPRT_DEVICE hiprtTraversalState getCurrentState();

  private:
	hiprtPimpl<
		hiprtGeomTraversal_impl<hiprtTriangleNode, hiprtTraversalTerminateAtClosestHit>,
		SIZE_GEOM_TRAVERSAL_PRIVATE_STACK,
		ALIGNMENT_GEOM_TRAVERSAL_PRIVATE_STACK>
		m_impl;
};

/** \brief A traversal object for finding the any hit with hiprtGeometry containing triangles.
 *
 * It uses a private stack with size 64 internally.
 */
class hiprtGeomTraversalAnyHit
{
  public:
	HIPRT_DEVICE hiprtGeomTraversalAnyHit(
		hiprtGeometry	   geom,
		const hiprtRay&	   ray,
		hiprtTraversalHint hint		 = hiprtTraversalHintDefault,
		void*			   payload	 = nullptr,
		hiprtFuncTable	   funcTable = nullptr,
		u32				   rayType	 = 0 );
	HIPRT_DEVICE hiprtHit			 getNextHit();
	HIPRT_DEVICE hiprtTraversalState getCurrentState();

  private:
	hiprtPimpl<
		hiprtGeomTraversal_impl<hiprtTriangleNode, hiprtTraversalTerminateAtAnyHit>,
		SIZE_GEOM_TRAVERSAL_PRIVATE_STACK,
		ALIGNMENT_GEOM_TRAVERSAL_PRIVATE_STACK>
		m_impl;
};

/** \brief A traversal object for finding the closest hit with hiprtGeometry containing custom primitives.
 *
 * It uses a private stack with size 64 internally.
 */
class hiprtGeomCustomTraversalClosest
{
  public:
	HIPRT_DEVICE hiprtGeomCustomTraversalClosest(
		hiprtGeometry	   geom,
		const hiprtRay&	   ray,
		hiprtTraversalHint hint		 = hiprtTraversalHintDefault,
		void*			   payload	 = nullptr,
		hiprtFuncTable	   funcTable = nullptr,
		u32				   rayType	 = 0 );
	HIPRT_DEVICE hiprtHit			 getNextHit();
	HIPRT_DEVICE hiprtTraversalState getCurrentState();

  private:
	hiprtPimpl<
		hiprtGeomTraversal_impl<hiprtCustomNode, hiprtTraversalTerminateAtClosestHit>,
		SIZE_GEOM_TRAVERSAL_PRIVATE_STACK,
		ALIGNMENT_GEOM_TRAVERSAL_PRIVATE_STACK>
		m_impl;
};

/** \brief A traversal object for finding the any hit with hiprtGeometry containing custom primitives.
 *
 * It uses a private stack with size 64 internally.
 */
class hiprtGeomCustomTraversalAnyHit
{
  public:
	HIPRT_DEVICE hiprtGeomCustomTraversalAnyHit(
		hiprtGeometry	   geom,
		const hiprtRay&	   ray,
		hiprtTraversalHint hint		 = hiprtTraversalHintDefault,
		void*			   payload	 = nullptr,
		hiprtFuncTable	   funcTable = nullptr,
		u32				   rayType	 = 0 );
	HIPRT_DEVICE hiprtHit			 getNextHit();
	HIPRT_DEVICE hiprtTraversalState getCurrentState();

  private:
	hiprtPimpl<
		hiprtGeomTraversal_impl<hiprtCustomNode, hiprtTraversalTerminateAtAnyHit>,
		SIZE_GEOM_TRAVERSAL_PRIVATE_STACK,
		ALIGNMENT_GEOM_TRAVERSAL_PRIVATE_STACK>
		m_impl;
};

/** \brief A traversal object for finding the closest hit with hiprtScene.
 *
 * It uses a private stack with size 64 internally.
 */
template <hiprtTraversalType TraversalType>
class hiprtSceneTraversal_impl;

class hiprtSceneTraversalClosest
{
  public:
	HIPRT_DEVICE hiprtSceneTraversalClosest(
		hiprtScene		   scene,
		const hiprtRay&	   ray,
		hiprtRayMask	   mask		 = hiprtFullRayMask,
		hiprtTraversalHint hint		 = hiprtTraversalHintDefault,
		void*			   payload	 = nullptr,
		hiprtFuncTable	   funcTable = nullptr,
		u32				   rayType	 = 0,
		float			   time		 = 0.0f );
	HIPRT_DEVICE hiprtHit			 getNextHit();
	HIPRT_DEVICE hiprtTraversalState getCurrentState();

  private:
	hiprtPimpl<
		hiprtSceneTraversal_impl<hiprtTraversalTerminateAtClosestHit>,
		SIZE_SCENE_TRAVERSAL_PRIVATE_STACK,
		ALIGNMENT_SCENE_TRAVERSAL_PRIVATE_STACK>
		m_impl;
};

/** \brief A traversal object for finding the any hit with hiprtScene.
 *
 * It uses a private stack with size 64 internally.
 */
class hiprtSceneTraversalAnyHit
{
  public:
	HIPRT_DEVICE hiprtSceneTraversalAnyHit(
		hiprtScene		   scene,
		const hiprtRay&	   ray,
		hiprtRayMask	   mask		 = hiprtFullRayMask,
		hiprtTraversalHint hint		 = hiprtTraversalHintDefault,
		void*			   payload	 = nullptr,
		hiprtFuncTable	   funcTable = nullptr,
		u32				   rayType	 = 0,
		float			   time		 = 0.0f );
	HIPRT_DEVICE hiprtHit			 getNextHit();
	HIPRT_DEVICE hiprtTraversalState getCurrentState();

  private:
	hiprtPimpl<
		hiprtSceneTraversal_impl<hiprtTraversalTerminateAtAnyHit>,
		SIZE_SCENE_TRAVERSAL_PRIVATE_STACK,
		ALIGNMENT_SCENE_TRAVERSAL_PRIVATE_STACK>
		m_impl;
};

/** \brief A traversal object for finding the closest hit with hiprtGeometry containing triangles.
 *
 * \tparam hiprtStack A custom stack.
 */
template <typename hiprtStack, hiprtPrimitiveNodeType PrimitiveNodeType, hiprtTraversalType TraversalType>
class hiprtGeomTraversalCustomStack_impl;

template <typename hiprtStack>
class hiprtGeomTraversalClosestCustomStack
{
  public:
	HIPRT_DEVICE hiprtGeomTraversalClosestCustomStack(
		hiprtGeometry	   geom,
		const hiprtRay&	   ray,
		hiprtStack&		   stack,
		hiprtTraversalHint hint		 = hiprtTraversalHintDefault,
		void*			   payload	 = nullptr,
		hiprtFuncTable	   funcTable = nullptr,
		u32				   rayType	 = 0 );
	HIPRT_DEVICE hiprtHit			 getNextHit();
	HIPRT_DEVICE hiprtTraversalState getCurrentState();

  private:
	hiprtPimpl<
		hiprtGeomTraversalCustomStack_impl<hiprtStack, hiprtTriangleNode, hiprtTraversalTerminateAtClosestHit>,
		SIZE_GEOM_TRAVERSAL_CUSTOM_STACK,
		ALIGNMENT_GEOM_TRAVERSAL_CUSTOM_STACK>
		m_impl;
};

/** \brief A traversal object for finding the any hit with hiprtGeometry containing triangles.
 *
 * \tparam hiprtStack A custom stack.
 */
template <typename hiprtStack>
class hiprtGeomTraversalAnyHitCustomStack
{
  public:
	HIPRT_DEVICE hiprtGeomTraversalAnyHitCustomStack(
		hiprtGeometry	   geom,
		const hiprtRay&	   ray,
		hiprtStack&		   stack,
		hiprtTraversalHint hint		 = hiprtTraversalHintDefault,
		void*			   payload	 = nullptr,
		hiprtFuncTable	   funcTable = nullptr,
		u32				   rayType	 = 0 );
	HIPRT_DEVICE hiprtHit			 getNextHit();
	HIPRT_DEVICE hiprtTraversalState getCurrentState();

  private:
	hiprtPimpl<
		hiprtGeomTraversalCustomStack_impl<hiprtStack, hiprtTriangleNode, hiprtTraversalTerminateAtAnyHit>,
		SIZE_GEOM_TRAVERSAL_CUSTOM_STACK,
		ALIGNMENT_GEOM_TRAVERSAL_CUSTOM_STACK>
		m_impl;
};

/** \brief A traversal object for finding the closest hit with hiprtGeometry containing custom primitives.
 *
 * \tparam hiprtStack A custom stack.
 */
template <typename hiprtStack>
class hiprtGeomCustomTraversalClosestCustomStack
{
  public:
	HIPRT_DEVICE hiprtGeomCustomTraversalClosestCustomStack(
		hiprtGeometry	   geom,
		const hiprtRay&	   ray,
		hiprtStack&		   stack,
		hiprtTraversalHint hint		 = hiprtTraversalHintDefault,
		void*			   payload	 = nullptr,
		hiprtFuncTable	   funcTable = nullptr,
		u32				   rayType	 = 0 );
	HIPRT_DEVICE hiprtHit			 getNextHit();
	HIPRT_DEVICE hiprtTraversalState getCurrentState();

  private:
	hiprtPimpl<
		hiprtGeomTraversalCustomStack_impl<hiprtStack, hiprtCustomNode, hiprtTraversalTerminateAtClosestHit>,
		SIZE_GEOM_TRAVERSAL_CUSTOM_STACK,
		ALIGNMENT_GEOM_TRAVERSAL_CUSTOM_STACK>
		m_impl;
};

/** \brief A traversal object for finding the any hit with hiprtGeometry containing custom primitives.
 *
 * \tparam hiprtStack A custom stack.
 */
template <typename hiprtStack>
class hiprtGeomCustomTraversalAnyHitCustomStack
{
  public:
	HIPRT_DEVICE hiprtGeomCustomTraversalAnyHitCustomStack(
		hiprtGeometry	   geom,
		const hiprtRay&	   ray,
		hiprtStack&		   stack,
		hiprtTraversalHint hint		 = hiprtTraversalHintDefault,
		void*			   payload	 = nullptr,
		hiprtFuncTable	   funcTable = nullptr,
		u32				   rayType	 = 0 );
	HIPRT_DEVICE hiprtHit			 getNextHit();
	HIPRT_DEVICE hiprtTraversalState getCurrentState();

  private:
	hiprtPimpl<
		hiprtGeomTraversalCustomStack_impl<hiprtStack, hiprtCustomNode, hiprtTraversalTerminateAtAnyHit>,
		SIZE_GEOM_TRAVERSAL_CUSTOM_STACK,
		ALIGNMENT_GEOM_TRAVERSAL_CUSTOM_STACK>
		m_impl;
};

/** \brief A traversal object for finding the closest hit with hiprtScene.
 *
 * \tparam hiprtStack A custom stack.
 */
template <typename hiprtStack, hiprtTraversalType TraversalType>
class hiprtSceneTraversalCustomStack_impl;

template <typename hiprtStack>
class hiprtSceneTraversalClosestCustomStack
{
  public:
	HIPRT_DEVICE hiprtSceneTraversalClosestCustomStack(
		hiprtScene		   scene,
		const hiprtRay&	   ray,
		hiprtStack&		   stack,
		hiprtRayMask	   mask		 = hiprtFullRayMask,
		hiprtTraversalHint hint		 = hiprtTraversalHintDefault,
		void*			   payload	 = nullptr,
		hiprtFuncTable	   funcTable = nullptr,
		u32				   rayType	 = 0,
		float			   time		 = 0.0f );
	HIPRT_DEVICE hiprtHit			 getNextHit();
	HIPRT_DEVICE hiprtTraversalState getCurrentState();

  private:
	hiprtPimpl<
		hiprtSceneTraversalCustomStack_impl<hiprtStack, hiprtTraversalTerminateAtClosestHit>,
		SIZE_SCENE_TRAVERSAL_CUSTOM_STACK,
		ALIGNMENT_SCENE_TRAVERSAL_CUSTOM_STACK>
		m_impl;
};

/** \brief A traversal object for finding the any hit with hiprtScene.
 *
 * \tparam hiprtStack A custom stack.
 */
template <typename hiprtStack>
class hiprtSceneTraversalAnyHitCustomStack
{
  public:
	HIPRT_DEVICE hiprtSceneTraversalAnyHitCustomStack(
		hiprtScene		   scene,
		const hiprtRay&	   ray,
		hiprtStack&		   stack,
		hiprtRayMask	   mask		 = hiprtFullRayMask,
		hiprtTraversalHint hint		 = hiprtTraversalHintDefault,
		void*			   payload	 = nullptr,
		hiprtFuncTable	   funcTable = nullptr,
		u32				   rayType	 = 0,
		float			   time		 = 0.0f );
	HIPRT_DEVICE hiprtHit			 getNextHit();
	HIPRT_DEVICE hiprtTraversalState getCurrentState();

  private:
	hiprtPimpl<
		hiprtSceneTraversalCustomStack_impl<hiprtStack, hiprtTraversalTerminateAtAnyHit>,
		SIZE_SCENE_TRAVERSAL_CUSTOM_STACK,
		ALIGNMENT_SCENE_TRAVERSAL_CUSTOM_STACK>
		m_impl;
};

/** \brief Returns the object to world transformation for a given instance and time in the form of the SRT frame.
 *
 * \param scene A scene.
 * \param instanceID Instance ID.
 * \param time The time.
 */
HIPRT_DEVICE hiprtFrameSRT hiprtGetObjectToWorldFrameSRT( hiprtScene scene, u32 instanceID, float time );

/** \brief Returns the world to object transformation for a given instance and time in the form of the SRT frame.
 *
 * \param scene A scene.
 * \param instanceID Instance ID.
 * \param time The time.
 */
HIPRT_DEVICE hiprtFrameSRT hiprtGetWorldToObjectFrameSRT( hiprtScene scene, u32 instanceID, float time );

/** \brief Returns the object to world transformation for a given instance and time in the form of the matrix.
 *
 * \param scene A scene.
 * \param instanceID Instance ID.
 * \param time The time.
 */
HIPRT_DEVICE hiprtFrameMatrix hiprtGetObjectToWorldFrameMatrix( hiprtScene scene, u32 instanceID, float time );

/** \brief Returns the world to object transformation for a given instance and time in the form of the matrix.
 *
 * \param scene A scene.
 * \param instanceID Instance ID.
 * \param time The time.
 */
HIPRT_DEVICE hiprtFrameMatrix hiprtGetWorldToObjectFrameMatrix( hiprtScene scene, u32 instanceID, float time );
