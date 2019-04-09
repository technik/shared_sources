/* Copyright (c) 2014-2018, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "appwindowprofiler_gl.hpp"

#include <nvh/misc.hpp>

namespace nvgl
{
  void AppWindowProfilerGL::contextInit()
  {
    // create OpenGL stuff at last
    m_contextWindow.init(&m_contextInfo, this);
    // create other additional OpenGL tools
    m_profilerGL.init();
  }

  void AppWindowProfilerGL::contextDeinit()
  {
    m_profilerGL.deinit();
    m_contextWindow.deinit();
  }

  void AppWindowProfilerGL::contextScreenshot( const char* bmpfilename, int width, int height )
  {
    std::vector<unsigned char> data;

    data.resize( width * height * 4 );
    glFinish();
    glBindFramebuffer( GL_READ_FRAMEBUFFER, 0 );
    glPixelStorei( GL_PACK_ALIGNMENT, 1 );
    glBindBuffer( GL_PIXEL_PACK_BUFFER, 0 );
    glReadPixels( 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, &data[0] );

    nvh::saveBMP( bmpfilename, width, height, &data[0] );
  }

}

