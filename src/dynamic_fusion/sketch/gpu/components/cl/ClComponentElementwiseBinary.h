/*
 * Copyright (c) 2022-2024 Arm Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef ACL_SRC_DYNAMIC_FUSION_SKETCH_GPU_COMPONENTS_CL_CLCOMPONENTELEMENTWISEBINARY_H
#define ACL_SRC_DYNAMIC_FUSION_SKETCH_GPU_COMPONENTS_CL_CLCOMPONENTELEMENTWISEBINARY_H

#include "src/dynamic_fusion/sketch/gpu/components/IGpuKernelComponent.h"
#include "src/dynamic_fusion/sketch/gpu/operators/internal/GpuElementwiseBinaryCommon.h"

namespace arm_compute
{
/** Forward declaration */
class ITensorInfo;
namespace experimental
{
namespace dynamic_fusion
{
/** Forward declaration */
template <typename T>
class ArgumentPack;

/** Forward declaration */
class GpuCkwElementwiseBinary;

class ClComponentElementwiseBinary final : public IGpuKernelComponent
{
public:
    /** Attributes are a set of backend-agnostic parameters that define what a component does */
    using Attributes = ElementwiseBinaryCommonAttributes;

public:
    /** Validate the component
     *
     * @param[in,out] tensors    Tensor arguments to the component
     * @param[in]     attributes Component attributes
     *
     * @return Status       Validation results
     *
     * Tensor argument names:
     * - ACL_SRC_0: lhs
     * - ACL_SRC_1: rhs
     * - ACL_DST_0: dst
     *
     * Tensor argument constness:
     * - ACL_SRC_0: Const
     * - ACL_SRC_1: Const
     * - ACL_DST_0: Const
     *
     * Valid data layouts:
     * - All
     *
     * Valid data type configurations (for DIV FP32/FP16/S32 supported, for POWER only FP32/FP16 supported):
     * |ACL_SRC_0      |ACL_SRC_1      |ACL_DST_0      |
     * |:--------------|:--------------|:--------------|
     * |F16            |F16            |F16            |
     * |F32            |F32            |F32            |
     * |S32            |S32            |S32            |
     * |S16            |S16            |S16            |
     * |U8             |U8             |U8             |
     */
    static Status validate(const ArgumentPack<ITensorInfo>         &tensors,
                           const ElementwiseBinaryCommonAttributes &attributes);

    /** Constructor
     *
     * Similar to @ref ClComponentElementwiseBinary::validate()
     */
    ClComponentElementwiseBinary(ComponentId                      id,
                                 const Properties                &properties,
                                 const ArgumentPack<ITensorInfo> &tensors,
                                 const Attributes                &attributes);

    /** Destructor */
    ~ClComponentElementwiseBinary() override;
    /** Prevent instances of this class from being copy constructed */
    ClComponentElementwiseBinary(const ClComponentElementwiseBinary &component) = delete;
    /** Prevent instances of this class from being copied */
    ClComponentElementwiseBinary &operator=(const ClComponentElementwiseBinary &component) = delete;
    /** Allow instances of this class to be move constructed */
    ClComponentElementwiseBinary(ClComponentElementwiseBinary &&component) = default;
    /** Allow instances of this class to be moved */
    ClComponentElementwiseBinary &operator=(ClComponentElementwiseBinary &&component) = default;
    /** Get writer for the component */
    const IGpuCkwComponentDriver *ckw_component_driver() const override;
    /** Get component type */
    GpuComponentType type() const override
    {
        return GpuComponentType::Simple;
    }

private:
    std::unique_ptr<GpuCkwElementwiseBinary> _component_writer;
};
} // namespace dynamic_fusion
} // namespace experimental
} // namespace arm_compute
#endif // ACL_SRC_DYNAMIC_FUSION_SKETCH_GPU_COMPONENTS_CL_CLCOMPONENTELEMENTWISEBINARY_H
