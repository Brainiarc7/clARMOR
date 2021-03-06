/********************************************************************************
 * Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ********************************************************************************/


/*! \file cl_image_to_buffer.h
 * context agnostic copy methods for cl_mem image to cl_mem buffer
 */

#ifndef __CL_IMAGE_TO_BUFFER_H
#define __CL_IMAGE_TO_BUFFER_H

#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#include <CL/cl.h>

/*!
 * Makes a copy of one cl_mem image into a flat cl_mem buffer
 * This function will cover all of the complexities of copying these images,
 * even if they were originally from different contexts.
 * To get the best performance, the command_queue should share the same context
 * as the 'src_image' cl_mem and the 'dst_buffer' cl_mem. If it does not, a new
 * command queue will be created internally.
 * If the context we must use already has oneo f these internal command queues,
 * we will use the cached version of it.
 *
 * \param command_queue
 *      command queue onto which the copy commands will
 *      nominally be enqueued. See above for cases where this
 *      will not actually be the queue used.
 * \param src_image
 *      cl_mem that holds the image we will be copying from
 * \param dst_buffer
 *      cl_mem that we are trying to copy into. Should already be
 *      created and have enough space to hold all of the copied data
 * \param src_origin
 *      3D offset into the 'src_image' start copying from
 * \param region
 *      3D size of the part of the source image to copy
 * \param dst_offset
 *      If we don't want to start writing into the beginning of
 *      the destination buffer, this is the offset to start at.
 * \param num_evt
 *      number of input events that this copy should wait on.
 * \param evt_list
 *      list of cl_events that should finish before the copy starts
 * \param out
 *      cl_event that will inform the outside world when the
 *      asynchronous copies within this command complete
 */
void inner_image_to_buffer_copy(cl_command_queue command_queue,
        cl_mem src_image, cl_mem dst_buffer, const size_t src_origin[3],
        const size_t region[3], size_t dst_offset, unsigned num_evt,
        const cl_event *evt_list, cl_event *out);

#endif // __CL_IMAGE_TO_BUFFER_H
