/*
 * Copyright (c) 2017-2021 Arm Limited.
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
#ifndef ARM_COMPUTE_CL_DEPTH_CONCATENATE_KERNEL_H
#define ARM_COMPUTE_CL_DEPTH_CONCATENATE_KERNEL_H

#include "src/core/common/Macros.h"
#include "src/gpu/cl/ClCompileContext.h"
#include "src/gpu/cl/IClKernel.h"

namespace arm_compute
{
namespace opencl
{
namespace kernels
{
/** Interface for the depth concatenate kernel.
 *  The src tensor will be concatenated into the dst tensor.
 */
class ClDepthConcatenateKernel : public IClKernel
{
public:
    ClDepthConcatenateKernel();
    ARM_COMPUTE_DISALLOW_COPY_ALLOW_MOVE(ClDepthConcatenateKernel);
    /** Initialise the kernel's source and destination
     *
     * @param[in]     compile_context The compile context to be used.
     * @param[in]     src             Source tensor info. Data types supported: QASYMM8/QASYMM8_SIGNED/F16/F32.
     * @param[in]     depth_offset    The offset on the Z axis.
     * @param[in,out] dst             Destination tensor info. Data types supported: Same as @p src.
     *
     * @note: The dst tensor's low two dimensions can't be smaller than the src one's.
     * @note: The gaps between the two lowest dimensions of src and dst need to be divisible by 2.
     *
     */
    void
    configure(const CLCompileContext &compile_context, ITensorInfo *src, unsigned int depth_offset, ITensorInfo *dst);
    /** Static function to check if given info will lead to a valid configuration
     *
     * Similar to @ref ClDepthConcatenateKernel::configure()
     *
     * @return a status
     */
    static Status validate(const ITensorInfo *src, unsigned int depth_offset, const ITensorInfo *dst);

    // Inherited methods overridden:
    void run_op(ITensorPack &tensors, const Window &window, ::cl::CommandQueue &queue) override;

private:
    unsigned int _depth_offset;
};
} // namespace kernels
} // namespace opencl
} // namespace arm_compute
#endif /* ARM_COMPUTE_CL_DEPTH_CONCATENATE_KERNEL_H */
