#pragma once

#if ( defined( __CUDACC__ ) || defined( __HIPCC__ ) )
#define __KERNELCC__
#endif

#include <hiprt/hiprt_vec.h>

struct _hiprtGeometry;
struct _hiprtScene;
struct _hiprtContext;
struct _hiprtFuncTable;

typedef void*			 hiprtDevicePtr;
typedef _hiprtGeometry*	 hiprtGeometry;
typedef _hiprtScene*	 hiprtScene;
typedef _hiprtContext*	 hiprtContext;
typedef _hiprtFuncTable* hiprtFuncTable;
typedef u32				 hiprtBuildFlags;
typedef u32				 hiprtRayMask;

typedef int	  hiprtApiDevice;	// hipDevice, cuDevice
typedef void* hiprtApiCtx;		// hipCtx, cuCtx
typedef void* hiprtApiStream;	// hipStream, cuStream
typedef void* hiprtApiFunction; // hipFunction, cuFunction
typedef void* hiprtApiModule;	// hipModule, cuModule

/** \brief Ray traversal type.
 *
 */
enum hiprtTraversalType
{
	/*!< 0 or 1 element iterator with any hit along the ray */
	hiprtTraversalTerminateAtAnyHit = 1,
	/*!< 0 or 1 element iterator with a closest hit along the ray */
	hiprtTraversalTerminateAtClosestHit = 2,
};

/** \brief Traversal state.
 *
 * On-device traversal can be in either hit state (and can be continued using
 * hiprtNextHit) or finished state.
 */
enum hiprtTraversalState
{
	hiprtTraversalStateInit,
	hiprtTraversalStateFinished,
	hiprtTraversalStateHit,
	hiprtTraversalStateStackOverflow
};

/** \brief Traversal hint.
 *
 * An additional information about the rays for the traversal object.
 * It is taken into account only on AMD Navi3x (RDNA3) and above.
 */
enum hiprtTraversalHint
{
	hiprtTraversalHintDefault		 = 0,
	hiprtTraversalHintShadowRays	 = 1,
	hiprtTraversalHintReflectionRays = 2
};

/** \brief Various constants.
 *
 */
enum : u32
{
	hiprtInvalidValue			   = hiprt::InvalidValue,
	hiprtFullRayMask			   = hiprt::FullRayMask,
	hiprtMaxBatchBuildMaxPrimCount = hiprt::MaxBatchBuildMaxPrimCount
};

/** \brief Error codes.
 *
 */
enum hiprtError
{
	hiprtSuccess				= 0,
	hiprtErrorNotImplemented	= 1,
	hiprtErrorInternal			= 2,
	hiprtErrorOutOfHostMemory	= 3,
	hiprtErrorOutOfDeviceMemory = 4,
	hiprtErrorInvalidApiVersion = 5,
	hiprtErrorInvalidParameter	= 6
};

/** \brief Log levels.
 *
 */
enum hiprtLogLevel
{
	hiprtLogLevelNone  = 0,
	hiprtLogLevelInfo  = 1 << 0,
	hiprtLogLevelWarn  = 1 << 1,
	hiprtLogLevelError = 1 << 2
};

/** \brief Type of geometry/scene build operation.
 *
 * hiprtBuildGeometry/hiprtBuildScene can either build or update
 * an underlying acceleration structure.
 */
enum hiprtBuildOperation
{
	hiprtBuildOperationBuild  = 1,
	hiprtBuildOperationUpdate = 2
};

/** \brief Hint flags for geometry/scene build functions.
 *
 * hiprtBuildGeometry/hiprtBuildScene use these flags to choose
 * an appropriate build format/algorithm.
 */
enum hiprtBuildFlagBits
{
	hiprtBuildFlagBitPreferFastBuild		= 0,
	hiprtBuildFlagBitPreferBalancedBuild	= 1,
	hiprtBuildFlagBitPreferHighQualityBuild = 2,
	hiprtBuildFlagBitCustomBvhImport		= 3,
	hiprtBuildFlagBitDisableSpatialSplits	= 1 << 2
};

/** \brief Geometric primitive type.
 *
 * hiprtGeometry can be built from multiple primitive types,
 * such as triangle meshes, AABB lists, line lists, etc. This enum
 * defines primitive type for hiprtBuildGeometry function.
 */
enum hiprtPrimitiveType
{
	hiprtPrimitiveTypeTriangleMesh,
	hiprtPrimitiveTypeAABBList
};

/** \brief primitve types
 *
 */
enum hiprtPrimitiveNodeType
{
	hiprtTriangleNode = 0,
	hiprtCustomNode	  = 1
};

/** \brief Transformation frame type.
 *
 */
enum hiprtFrameType
{
	hiprtFrameTypeSRT,
	hiprtFrameTypeMatrix
};

/** \brief Stack type.
 *
 */
enum hiprtStackType
{
	hiprtStackTypeGlobal,
	hiprtStackTypeDynamic
};

/** \brief Bvh node type.
 *
 */
enum hiprtBvhNodeType
{
	/*!< Leaf node */
	hiprtBvhNodeTypeInternal = 0,
	/*!< Internal node */
	hiprtBvhNodeTypeLeaf = 1,
};

/** \brief Ray data structure.
 *
 */
struct alignas( 32 ) hiprtRay
{
	/*!< Ray origin */
	hiprtFloat3 origin;
	/*!< Ray maximum distance */
	float minT = 0.0f;
	/*!< Ray direction */
	hiprtFloat3 direction;
	/*!< Ray maximum distance */
	float maxT = hiprt::FltMax;
};
HIPRT_STATIC_ASSERT( sizeof( hiprtRay ) == 32 );

/** \brief Ray hit data structure.
 *
 */
struct alignas( 32 ) hiprtHit
{
	/*!< Instance ID */
	u32 instanceID = hiprtInvalidValue;
	/*!< Primitive ID */
	u32 primID = hiprtInvalidValue;
	/*!< Texture coordinates */
	hiprtFloat2 uv;
	/*!< Geeometric normal (not normalized) */
	hiprtFloat3 normal;
	/*!< Distance */
	float t = -1.0f;

	HIPRT_DEVICE bool hasHit() const { return primID != hiprtInvalidValue; }
};
HIPRT_STATIC_ASSERT( sizeof( hiprtHit ) == 32 );

/** \brief Set of device data pointers for custom functions.
 *
 */
struct hiprtFuncDataSet
{
	const void* intersectFuncData = nullptr;
	const void* filterFuncData	  = nullptr;
};

/** \brief A header of the function table.
 *
 */
struct hiprtFuncTableHeader
{
	u32				  numGeomTypes;
	u32				  numRayTypes;
	hiprtFuncDataSet* funcDataSets;
};

/** \brief A header of the global stack buffer.
 * Use API functions to create this buffer.
 * - hiprtCreateStackBuffer
 * - hiprtDestroyStackBuffer
 */
struct hiprtGlobalStackBuffer
{
	u32	 stackSize;
	u32	 stackCount;
	int* stackData;
};

/** \brief A header of the shared stack buffer.
 *
 */
struct hiprtSharedStackBuffer
{
	u32	 stackSize;
	int* stackData;
};

/** \brief Set of function names.
 *
 */
struct hiprtFuncNameSet
{
	const char* intersectFuncName = nullptr;
	const char* filterFuncName	  = nullptr;
};

/** \brief Device type.
 *
 */
enum hiprtDeviceType
{
	/*!< AMD device */
	hiprtDeviceAMD,
	/*!< Nvidia device */
	hiprtDeviceNVIDIA,
};

/** \brief Context creation input.
 *
 */
struct hiprtContextCreationInput
{
	/*!< HIPRT API context */
	hiprtApiCtx ctxt;
	/*!< HIPRT API device */
	hiprtApiDevice device;
	/*!< HIPRT API device type */
	hiprtDeviceType deviceType;
};

/** \brief Various flags controlling scene/geometry build process.
 *
 */
struct hiprtBuildOptions
{
	/*!< Build flags */
	hiprtBuildFlags buildFlags;
	/*!< Batch build max prim count (if 0 then batch build is not used) */
	u32 batchBuildMaxPrimCount = 0u;
};

/** \brief Triangle mesh primitive.
 *
 * Triangle mesh primitive is represented as an indexed vertex array.
 * Vertex and index arrays are defined using device pointers and strides.
 * Each vertex has to have 3 components: (x, y, z) coordinates.
 * Indices are organized into triples (i0, i1, i2) - one for each triangle.
 */
struct hiprtTriangleMeshPrimitive
{
	/*!< Device pointer to vertex data */
	hiprtDevicePtr vertices;
	/*!< Number of vertices in vertex array */
	u32 vertexCount;
	/*!< Stride in bytes between two vertices */
	u32 vertexStride;

	/*!< Device pointer to index data */
	hiprtDevicePtr triangleIndices;
	/*!< Number of trinagles in index array */
	u32 triangleCount;
	/*!< Stride in bytes between two triangles */
	u32 triangleStride;
};

/** \brief AABB list primitive.
 *
 * AABB list is an array of axis aligned bounding boxes, represented
 * by device memory pointer and stride between two consequetive boxes.
 * Each AABB is a pair of float3 or float4 values.
 */
struct hiprtAABBListPrimitive
{
	/*!< Device pointer to AABB data */
	hiprtDevicePtr aabbs;
	/*!< Number of AABBs in the array */
	u32 aabbCount;
	/*!< Stride in bytes between two AABBs (2 * sizeof(float3) or 2 * sizeof(float4)) */
	u32 aabbStride;
};

/** \brief Bvh node for custom import Bvh.
 *
 */
struct alignas( 64 ) hiprtBvhNode
{
	/*!< Child indices (empty slot needs to be marked by hiprtInvalidValue) */
	u32 childIndices[4];
	/*!< Child node types */
	hiprtBvhNodeType childNodeTypes[4];
	/*!< Node bounding box min */
	hiprtFloat3 boundingBoxMin;
	/*!< Node bounding box max */
	hiprtFloat3 boundingBoxMax;
};
HIPRT_STATIC_ASSERT( sizeof( hiprtBvhNode ) == 64 );

/** \brief Bvh node list.
 *
 */
struct hiprtBvhNodeList
{
	/*!< Array of hiprtBvhNode's */
	hiprtDevicePtr nodes;
	/*!< Number of nodes */
	u32 nodeCount;
};

/** \brief Build input for geometry build/update operation.
 *
 * Build input defines concrete primitive type and a pointer to an actual
 * primitive description.
 */
struct alignas( 16 ) hiprtGeometryBuildInput
{
	/*!< Primitive type */
	hiprtPrimitiveType type;
	/*!< Geometry type used for custom function table */
	u32 geomType = hiprtInvalidValue;
	/*!< Defines the following union */
	union
	{
		struct
		{
			/*!< Triangle mesh */
			hiprtTriangleMeshPrimitive primitive;
		} triangleMesh;
		struct
		{
			/*!< Bounding boxes of custom primitives */
			hiprtAABBListPrimitive primitive;
		} aabbList;
	};
	/*!< Custom Bvh nodes (optional) */
	hiprtBvhNodeList* nodes;
};
HIPRT_STATIC_ASSERT( sizeof( hiprtGeometryBuildInput ) == 48 );

/** \brief Build input for the scene.
 *
 * Scene consists of a set of instances. Each of the instances is defined by:
 *  - Root pointer of the corresponding geometry
 *  - Transformation header
 *  - Mask
 *
 * Instances can refer to the same geometry but with different transformations
 * (essentially implementing instancing). Mask is used to implement ray
 * masking: ray mask is bitwise &ded with an instance mask, and no intersections
 * are evaluated with the primitive of corresponding instance if the result is
 * 0. The transformation header defines the offset and the number of consecutive
 * transformation frames in the frame array for each instance. More than one frame
 * is interpreted as motion blur. If the transformation headers is NULL, it
 * assumes one frame per instance. Optionally, it is possible to import a custom
 * BVH by setting nodes and the corresponding build flag.
 */
struct alignas( 16 ) hiprtSceneBuildInput
{
	/*!< Array of instanceCount pointers to geometries */
	hiprtDevicePtr instanceGeometries;
	/*!< Array of instanceCount transform headers (optional: per object frame assumed if NULL) */
	hiprtDevicePtr instanceTransformHeaders;
	/*!< Array of frameCount frames (supposed to be ordered according to time) */
	hiprtDevicePtr instanceFrames;
	/*!< Per object bit masks for instance masking (optional: if NULL masks treated as hiprtFullRayMask) */
	hiprtDevicePtr instanceMasks;
	/*!< Custom Bvh nodes (optional) */
	hiprtBvhNodeList* nodes;
	/*!< Number of instances */
	u32 instanceCount;
	/*!< Number of frames (such that instanceCount <= frameCount) */
	u32 frameCount;
	/*!< Frame type (SRT or matrix) */
	hiprtFrameType frameType = hiprtFrameTypeSRT;
};
HIPRT_STATIC_ASSERT( sizeof( hiprtSceneBuildInput ) == 64 );

/** \brief Input for the global stack buffer allocation
 *
 */
struct hiprtGlobalStackBufferInput
{
	/*!< Stack type */
	hiprtStackType type = hiprtStackTypeGlobal;
	/*!< Global stack size (e.g. 64) */
	u32 stackSize;
	/*!< Total number of threads (for hiprtGlobalStack only) */
	u32 threadCount;
};

/** \brief SRT transformation frame.
 *
 * Represented by scale (S), rotation (R), translation (T), and frame time.
 * Object to world transformation is composed as (T * R * S) * x = y
 */
struct alignas( 16 ) hiprtFrameSRT
{
	/*!< Rotation (axis and angle) */
	hiprtFloat4 rotation;
	/*!< Scale */
	hiprtFloat3 scale;
	/*!< Translation */
	hiprtFloat3 translation;
	/*!< Frame time */
	float time;
};
HIPRT_STATIC_ASSERT( sizeof( hiprtFrameSRT ) == 48 );

/** \brief Transformation matrix frame representation.
 *
 * Represented by a 3x4 matrix and frame time.
 */
struct alignas( 64 ) hiprtFrameMatrix
{
	/*!< Matrix */
	float matrix[3][4];
	/*!< Frame time */
	float time;
};
HIPRT_STATIC_ASSERT( sizeof( hiprtFrameMatrix ) == 64 );

/** \brief Transformation header.
 *
 * Defines defines the index to the array of frames and the number of frames.
 */
struct alignas( 8 ) hiprtTransformHeader
{
	/*!< Frame index */
	u32 frameIndex;
	/*!< Number of frames */
	u32 frameCount;
};
HIPRT_STATIC_ASSERT( sizeof( hiprtTransformHeader ) == 8 );
