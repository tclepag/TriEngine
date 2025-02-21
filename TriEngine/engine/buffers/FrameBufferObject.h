//
// Created by lepag on 2/18/2025.
//

#ifndef FRAMEBUFFEROBJECT_H
#define FRAMEBUFFEROBJECT_H

#include <glad/glad.h>
#include <iostream>

namespace tri::buffers {
    class FrameBufferObject {
    public:
        GLuint id;
        GLuint texture;

        FrameBufferObject(): id(0) {
          glGenFramebuffers(1, &id);

          glBindFramebuffer(GL_FRAMEBUFFER, id);

          glGenTextures(1, &texture);
          glBindTexture(GL_TEXTURE_2D, texture);
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

          if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer is not complete!" << std::endl;

        }

        ~FrameBufferObject() {
          glDeleteFramebuffers(1, &id);
        }

        void bind() const {
          glBindFramebuffer(GL_FRAMEBUFFER, id);
        }

        void unbind() {
          glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void dispose() {
          delete this;
        }
    };
}

#endif //FRAMEBUFFEROBJECT_H
