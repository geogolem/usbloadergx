/* gecko.c
 *   by Alex Chadwick
 * 
 * Copyright (C) 2014, Alex Chadwick
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <bslug.h>
#include <hook.h>
#include <rvl/cache.h>
#include <string.h>

BSLUG_MODULE_GAME("????");
BSLUG_MODULE_NAME("USB Gecko Hook");
BSLUG_MODULE_VERSION("v1.0");
BSLUG_MODULE_AUTHOR("Chadderz");
BSLUG_MODULE_LICENSE("BSD");

void _start(void);

static const unsigned char codehandler[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x27, 0x74, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94, 0x21, 0xff, 0x58, 0x90, 0x01, 0x00, 0x08,
    0x7c, 0x08, 0x02, 0xa6, 0x90, 0x01, 0x00, 0xac, 0x7c, 0x00, 0x00, 0x26, 0x90, 0x01, 0x00, 0x0c,
    0x7c, 0x09, 0x02, 0xa6, 0x90, 0x01, 0x00, 0x10, 0x7c, 0x01, 0x02, 0xa6, 0x90, 0x01, 0x00, 0x14,
    0xbc, 0x61, 0x00, 0x18, 0x7f, 0x20, 0x00, 0xa6, 0x63, 0x3a, 0x20, 0x00, 0x73, 0x5a, 0xf9, 0xff,
    0x7f, 0x40, 0x01, 0x24, 0xd8, 0x41, 0x00, 0x98, 0xd8, 0x61, 0x00, 0xa0, 0x3f, 0xe0, 0x80, 0x00,
    0x3e, 0x80, 0xcc, 0x00, 0xa3, 0x94, 0x40, 0x10, 0x63, 0x95, 0x00, 0xff, 0xb2, 0xb4, 0x40, 0x10,
    0x48, 0x00, 0x06, 0x55, 0x3a, 0xa0, 0x00, 0x00, 0x3a, 0xc0, 0x00, 0x19, 0x3a, 0xe0, 0x00, 0xd0,
    0x3f, 0x00, 0xcd, 0x00, 0x63, 0xf2, 0x27, 0x74, 0x80, 0x01, 0x00, 0xac, 0x90, 0x12, 0x00, 0x04,
    0x92, 0xb8, 0x64, 0x3c, 0x48, 0x00, 0x04, 0x2d, 0x41, 0x82, 0x05, 0xa4, 0x2c, 0x1d, 0x00, 0x04,
    0x40, 0x80, 0x00, 0x10, 0x2c, 0x1d, 0x00, 0x01, 0x41, 0x80, 0x05, 0x94, 0x48, 0x00, 0x03, 0x4c,
    0x41, 0x82, 0x04, 0xf0, 0x2c, 0x1d, 0x00, 0x06, 0x41, 0x82, 0x00, 0x8c, 0x2c, 0x1d, 0x00, 0x07,
    0x41, 0x82, 0x03, 0x30, 0x2c, 0x1d, 0x00, 0x08, 0x41, 0x82, 0x05, 0x80, 0x2c, 0x1d, 0x00, 0x09,
    0x41, 0x82, 0x00, 0xa0, 0x2c, 0x1d, 0x00, 0x10, 0x41, 0x82, 0x00, 0x98, 0x2c, 0x1d, 0x00, 0x2f,
    0x41, 0x82, 0x00, 0x70, 0x2c, 0x1d, 0x00, 0x30, 0x41, 0x82, 0x00, 0x78, 0x2c, 0x1d, 0x00, 0x38,
    0x41, 0x82, 0x05, 0x28, 0x2c, 0x1d, 0x00, 0x40, 0x41, 0x82, 0x03, 0x40, 0x2c, 0x1d, 0x00, 0x41,
    0x41, 0x82, 0x03, 0x58, 0x2c, 0x1d, 0x00, 0x44, 0x41, 0x82, 0x00, 0x68, 0x2c, 0x1d, 0x00, 0x50,
    0x41, 0x82, 0x00, 0x20, 0x2c, 0x1d, 0x00, 0x60, 0x41, 0x82, 0x00, 0x24, 0x2c, 0x1d, 0x00, 0x89,
    0x41, 0x82, 0x00, 0x50, 0x2c, 0x1d, 0x00, 0x99, 0x41, 0x82, 0x05, 0x0c, 0x48, 0x00, 0x05, 0x10,
    0x80, 0x72, 0x00, 0x00, 0x48, 0x00, 0x04, 0x29, 0x48, 0x00, 0x05, 0x04, 0x48, 0x00, 0x05, 0x89,
    0x48, 0x00, 0x04, 0xfc, 0x38, 0x80, 0x00, 0x01, 0x90, 0x92, 0x00, 0x00, 0x48, 0x00, 0x04, 0xf0,
    0x48, 0x00, 0x04, 0x09, 0x3a, 0x00, 0x00, 0xa0, 0x63, 0xec, 0x27, 0x98, 0x48, 0x00, 0x03, 0x14,
    0x38, 0x60, 0x01, 0x20, 0x63, 0xec, 0x27, 0x98, 0x48, 0x00, 0x03, 0xc9, 0x48, 0x00, 0x04, 0xd0,
    0x2f, 0x1d, 0x00, 0x10, 0x2e, 0x9d, 0x00, 0x44, 0x63, 0xe4, 0x1a, 0xb4, 0x3c, 0x60, 0x80, 0x00,
    0x60, 0x63, 0x03, 0x00, 0x48, 0x00, 0x05, 0x09, 0x38, 0x63, 0x0a, 0x00, 0x48, 0x00, 0x05, 0x01,
    0x38, 0x63, 0x06, 0x00, 0x48, 0x00, 0x04, 0xf9, 0x63, 0xec, 0x27, 0x88, 0x92, 0xac, 0x00, 0x00,
    0x92, 0xac, 0x00, 0x04, 0x92, 0xac, 0x00, 0x08, 0x63, 0xe4, 0x27, 0x98, 0x81, 0x24, 0x00, 0x18,
    0x80, 0x72, 0x00, 0x00, 0x2c, 0x03, 0x00, 0x02, 0x40, 0x82, 0x00, 0x0c, 0x41, 0x96, 0x00, 0x0c,
    0x48, 0x00, 0x00, 0x20, 0x38, 0x60, 0x00, 0x00, 0x90, 0x6c, 0x00, 0x0c, 0x40, 0x82, 0x00, 0x14,
    0x40, 0x96, 0x00, 0x10, 0x61, 0x29, 0x04, 0x00, 0x91, 0x24, 0x00, 0x18, 0x48, 0x00, 0x02, 0x14,
    0x55, 0x29, 0x05, 0xa8, 0x91, 0x24, 0x00, 0x18, 0x41, 0x96, 0x04, 0x54, 0x41, 0x9a, 0x00, 0x08,
    0x39, 0x8c, 0x00, 0x04, 0x38, 0x60, 0x00, 0x04, 0x48, 0x00, 0x03, 0x09, 0x40, 0x99, 0x00, 0x10,
    0x39, 0x8c, 0x00, 0x04, 0x38, 0x60, 0x00, 0x04, 0x48, 0x00, 0x02, 0xf9, 0x63, 0xe4, 0x27, 0x88,
    0x80, 0x64, 0x00, 0x00, 0x80, 0x84, 0x00, 0x04, 0x7c, 0x72, 0xfb, 0xa6, 0x7c, 0x95, 0xfb, 0xa6,
    0x48, 0x00, 0x04, 0x1c, 0x7c, 0x32, 0x43, 0xa6, 0x7c, 0x3a, 0x02, 0xa6, 0x7c, 0x73, 0x43, 0xa6,
    0x7c, 0x7b, 0x02, 0xa6, 0x54, 0x63, 0x05, 0xa8, 0x90, 0x60, 0x27, 0xb0, 0x54, 0x63, 0x06, 0x1e,
    0x60, 0x63, 0x20, 0x00, 0x7c, 0x7b, 0x03, 0xa6, 0x3c, 0x60, 0x80, 0x00, 0x60, 0x63, 0x1a, 0xe8,
    0x7c, 0x7a, 0x03, 0xa6, 0x4c, 0x00, 0x00, 0x64, 0x3c, 0x60, 0x80, 0x00, 0x60, 0x63, 0x27, 0x98,
    0x90, 0x23, 0x00, 0x14, 0x7c, 0x61, 0x1b, 0x78, 0x7c, 0x73, 0x42, 0xa6, 0xbc, 0x41, 0x00, 0x24,
    0x7c, 0x24, 0x0b, 0x78, 0x7c, 0x32, 0x42, 0xa6, 0x90, 0x04, 0x00, 0x1c, 0x90, 0x24, 0x00, 0x20,
    0x7c, 0x68, 0x02, 0xa6, 0x90, 0x64, 0x00, 0x9c, 0x7c, 0x60, 0x00, 0x26, 0x90, 0x64, 0x00, 0x00,
    0x7c, 0x61, 0x02, 0xa6, 0x90, 0x64, 0x00, 0x04, 0x7c, 0x69, 0x02, 0xa6, 0x90, 0x64, 0x00, 0x08,
    0x7c, 0x72, 0x02, 0xa6, 0x90, 0x64, 0x00, 0x0c, 0x7c, 0x73, 0x02, 0xa6, 0x90, 0x64, 0x00, 0x10,
    0x39, 0x20, 0x00, 0x00, 0x7d, 0x32, 0xfb, 0xa6, 0x7d, 0x35, 0xfb, 0xa6, 0x3c, 0xa0, 0x80, 0x00,
    0x60, 0xa5, 0x1b, 0x70, 0x3f, 0xe0, 0xd0, 0x04, 0x63, 0xff, 0x00, 0xa0, 0x93, 0xe5, 0x00, 0x00,
    0x7c, 0x00, 0x28, 0x6c, 0x7c, 0x00, 0x04, 0xac, 0x7c, 0x00, 0x2f, 0xac, 0x4c, 0x00, 0x01, 0x2c,
    0xd0, 0x04, 0x00, 0xa0, 0x3b, 0xff, 0x00, 0x04, 0x3f, 0xff, 0x00, 0x20, 0x57, 0xf0, 0x01, 0x4b,
    0x41, 0x82, 0xff, 0xdc, 0x3f, 0xe0, 0x80, 0x00, 0x63, 0xe5, 0x27, 0x88, 0x82, 0x05, 0x00, 0x00,
    0x82, 0x25, 0x00, 0x04, 0x82, 0x65, 0x00, 0x0c, 0x2c, 0x13, 0x00, 0x00, 0x41, 0x82, 0x00, 0x74,
    0x2c, 0x13, 0x00, 0x02, 0x40, 0x82, 0x00, 0x18, 0x81, 0x24, 0x00, 0x14, 0x39, 0x33, 0x00, 0x03,
    0x91, 0x25, 0x00, 0x00, 0x91, 0x25, 0x00, 0x0c, 0x48, 0x00, 0x00, 0x6c, 0x7c, 0x10, 0x98, 0x00,
    0x41, 0x82, 0x00, 0x38, 0x7c, 0x11, 0x98, 0x00, 0x41, 0x82, 0x00, 0x30, 0x7d, 0x30, 0x8a, 0x14,
    0x91, 0x25, 0x00, 0x0c, 0x82, 0x05, 0x00, 0x08, 0x2c, 0x10, 0x00, 0x00, 0x41, 0x82, 0x00, 0x48,
    0x80, 0x64, 0x00, 0x10, 0x7c, 0x10, 0x18, 0x00, 0x40, 0x82, 0x00, 0x10, 0x3a, 0x00, 0x00, 0x00,
    0x92, 0x05, 0x00, 0x08, 0x48, 0x00, 0x00, 0x30, 0x3a, 0x20, 0x00, 0x00, 0x92, 0x25, 0x00, 0x0c,
    0x81, 0x24, 0x00, 0x18, 0x61, 0x29, 0x04, 0x00, 0x91, 0x24, 0x00, 0x18, 0x48, 0x00, 0x00, 0x30,
    0x7e, 0x12, 0xfb, 0xa6, 0x7e, 0x35, 0xfb, 0xa6, 0x39, 0x20, 0x00, 0x01, 0x91, 0x25, 0x00, 0x0c,
    0x48, 0x00, 0x00, 0x1c, 0x38, 0xa0, 0x00, 0x02, 0x63, 0xe4, 0x27, 0x74, 0x90, 0xa4, 0x00, 0x00,
    0x38, 0x60, 0x00, 0x11, 0x48, 0x00, 0x01, 0xb9, 0x4b, 0xff, 0xfc, 0x71, 0x7c, 0x20, 0x00, 0xa6,
    0x54, 0x21, 0x07, 0xfa, 0x54, 0x21, 0x04, 0x5e, 0x7c, 0x20, 0x01, 0x24, 0x63, 0xe1, 0x27, 0x98,
    0x80, 0x61, 0x00, 0x00, 0x7c, 0x6f, 0xf1, 0x20, 0x80, 0x61, 0x00, 0x14, 0x7c, 0x7a, 0x03, 0xa6,
    0x80, 0x61, 0x00, 0x18, 0x7c, 0x7b, 0x03, 0xa6, 0x80, 0x61, 0x00, 0x9c, 0x7c, 0x68, 0x03, 0xa6,
    0xb8, 0x41, 0x00, 0x24, 0x80, 0x01, 0x00, 0x1c, 0x80, 0x21, 0x00, 0x20, 0x4c, 0x00, 0x00, 0x64,
    0x92, 0xb2, 0x00, 0x00, 0x48, 0x00, 0x02, 0x54, 0x2e, 0x9d, 0x00, 0x02, 0x38, 0x60, 0x00, 0x08,
    0x63, 0xec, 0x27, 0x7c, 0x48, 0x00, 0x00, 0xfd, 0x80, 0xac, 0x00, 0x00, 0x80, 0x6c, 0x00, 0x04,
    0x98, 0x65, 0x00, 0x00, 0x41, 0x94, 0x00, 0x10, 0xb0, 0x65, 0x00, 0x00, 0x41, 0x96, 0x00, 0x08,
    0x90, 0x65, 0x00, 0x00, 0x7c, 0x00, 0x28, 0xac, 0x7c, 0x00, 0x04, 0xac, 0x7c, 0x00, 0x2f, 0xac,
    0x4c, 0x00, 0x01, 0x2c, 0x48, 0x00, 0x02, 0x08, 0x48, 0x00, 0x01, 0x21, 0x38, 0x60, 0x00, 0x04,
    0x63, 0xec, 0x27, 0x7c, 0x48, 0x00, 0x00, 0xbd, 0x82, 0x0c, 0x00, 0x00, 0x3d, 0x80, 0x80, 0x00,
    0x61, 0x8c, 0x28, 0xb8, 0x48, 0x00, 0x00, 0x1c, 0x48, 0x00, 0x01, 0x01, 0x38, 0x60, 0x00, 0x08,
    0x63, 0xec, 0x27, 0x7c, 0x48, 0x00, 0x00, 0x9d, 0x82, 0x0c, 0x00, 0x04, 0x81, 0x8c, 0x00, 0x00,
    0x63, 0xfb, 0x27, 0x84, 0x3a, 0x20, 0x0f, 0x80, 0x48, 0x00, 0x02, 0x39, 0x41, 0x82, 0x00, 0x20,
    0x7e, 0x23, 0x8b, 0x78, 0x48, 0x00, 0x00, 0x7d, 0x48, 0x00, 0x00, 0xd1, 0x41, 0x82, 0xff, 0xfc,
    0x7d, 0x8c, 0x72, 0x14, 0x35, 0x6b, 0xff, 0xff, 0x41, 0x81, 0xff, 0xe8, 0x80, 0x7b, 0x00, 0x00,
    0x2c, 0x03, 0x00, 0x00, 0x41, 0x82, 0x00, 0x08, 0x48, 0x00, 0x00, 0x59, 0x7c, 0x00, 0x60, 0xac,
    0x7c, 0x00, 0x04, 0xac, 0x7c, 0x00, 0x67, 0xac, 0x4c, 0x00, 0x01, 0x2c, 0x48, 0x00, 0x01, 0x80,
    0x7f, 0xc8, 0x02, 0xa6, 0x3c, 0x60, 0xa0, 0x00, 0x48, 0x00, 0x00, 0x15, 0x76, 0x03, 0x08, 0x00,
    0x56, 0x1d, 0x86, 0x3e, 0x7f, 0xc8, 0x03, 0xa6, 0x4e, 0x80, 0x00, 0x20, 0x92, 0xf8, 0x68, 0x14,
    0x90, 0x78, 0x68, 0x24, 0x92, 0xd8, 0x68, 0x20, 0x80, 0xb8, 0x68, 0x20, 0x70, 0xa5, 0x00, 0x01,
    0x40, 0x82, 0xff, 0xf8, 0x82, 0x18, 0x68, 0x24, 0x90, 0xb8, 0x68, 0x14, 0x4e, 0x80, 0x00, 0x20,
    0x7d, 0x48, 0x02, 0xa6, 0x7c, 0x69, 0x03, 0xa6, 0x39, 0xc0, 0x00, 0x00, 0x48, 0x00, 0x00, 0x79,
    0x48, 0x00, 0x00, 0x75, 0x4b, 0xff, 0xff, 0xad, 0x41, 0x82, 0xff, 0xf4, 0x7f, 0xae, 0x61, 0xae,
    0x39, 0xce, 0x00, 0x01, 0x42, 0x00, 0xff, 0xe8, 0x7d, 0x48, 0x03, 0xa6, 0x4e, 0x80, 0x00, 0x20,
    0x7d, 0x48, 0x02, 0xa6, 0x7c, 0x69, 0x03, 0xa6, 0x39, 0xc0, 0x00, 0x00, 0x7c, 0x6c, 0x70, 0xae,
    0x48, 0x00, 0x00, 0x1d, 0x41, 0x82, 0xff, 0xf8, 0x39, 0xce, 0x00, 0x01, 0x42, 0x00, 0xff, 0xf0,
    0x7d, 0x48, 0x03, 0xa6, 0x4e, 0x80, 0x00, 0x20, 0x38, 0x60, 0x00, 0xaa, 0x7f, 0xc8, 0x02, 0xa6,
    0x54, 0x63, 0xa0, 0x16, 0x64, 0x63, 0xb0, 0x00, 0x3a, 0xc0, 0x00, 0x19, 0x3a, 0xe0, 0x00, 0xd0,
    0x3f, 0x00, 0xcd, 0x00, 0x4b, 0xff, 0xff, 0x69, 0x56, 0x03, 0x37, 0xff, 0x7f, 0xc8, 0x03, 0xa6,
    0x4e, 0x80, 0x00, 0x20, 0x7f, 0xc8, 0x02, 0xa6, 0x3c, 0x60, 0xd0, 0x00, 0x4b, 0xff, 0xff, 0x51,
    0x56, 0x03, 0x37, 0xff, 0x41, 0x82, 0xff, 0xf4, 0x7f, 0xc8, 0x03, 0xa6, 0x4e, 0x80, 0x00, 0x20,
    0x4b, 0xff, 0xff, 0xb9, 0x38, 0x60, 0x00, 0x08, 0x63, 0xec, 0x27, 0x7c, 0x4b, 0xff, 0xff, 0x55,
    0x80, 0xac, 0x00, 0x04, 0x81, 0x8c, 0x00, 0x00, 0x63, 0xfb, 0x27, 0x84, 0x62, 0xb1, 0xf8, 0x00,
    0x7e, 0x0c, 0x28, 0x50, 0x48, 0x00, 0x00, 0xed, 0x41, 0x81, 0x00, 0x10, 0x82, 0x3b, 0x00, 0x00,
    0x2c, 0x11, 0x00, 0x00, 0x41, 0x82, 0x00, 0x68, 0x7e, 0x23, 0x8b, 0x78, 0x4b, 0xff, 0xff, 0x55,
    0x4b, 0xff, 0xff, 0xa5, 0x4b, 0xff, 0xff, 0xa1, 0x4b, 0xff, 0xfe, 0xd9, 0x41, 0x82, 0xff, 0xf4,
    0x2c, 0x1d, 0x00, 0xcc, 0x41, 0x82, 0x00, 0x48, 0x2c, 0x1d, 0x00, 0xbb, 0x41, 0x82, 0xff, 0xdc,
    0x2c, 0x1d, 0x00, 0xaa, 0x40, 0x82, 0xff, 0xdc, 0x7d, 0x8c, 0x72, 0x14, 0x35, 0x6b, 0xff, 0xff,
    0x41, 0x80, 0x00, 0x2c, 0x4b, 0xff, 0xff, 0xb4, 0x7e, 0xb5, 0xfb, 0xa6, 0x7e, 0xb2, 0xfb, 0xa6,
    0x63, 0xe4, 0x27, 0x98, 0x81, 0x24, 0x00, 0x18, 0x55, 0x29, 0x05, 0xa8, 0x91, 0x24, 0x00, 0x18,
    0x48, 0x00, 0x00, 0x0c, 0x38, 0x60, 0x00, 0x80, 0x4b, 0xff, 0xff, 0x25, 0x80, 0x92, 0x00, 0x00,
    0x2c, 0x04, 0x00, 0x00, 0x40, 0x82, 0xfa, 0x50, 0xb3, 0x94, 0x40, 0x10, 0xc8, 0x41, 0x00, 0x98,
    0xc8, 0x61, 0x00, 0xa0, 0x7f, 0x20, 0x00, 0xa6, 0x80, 0x01, 0x00, 0xac, 0x7c, 0x08, 0x03, 0xa6,
    0x80, 0x01, 0x00, 0x0c, 0x7c, 0x0f, 0xf1, 0x20, 0x80, 0x01, 0x00, 0x10, 0x7c, 0x09, 0x03, 0xa6,
    0x80, 0x01, 0x00, 0x14, 0x7c, 0x01, 0x03, 0xa6, 0xb8, 0x61, 0x00, 0x18, 0x80, 0x01, 0x00, 0x08,
    0x38, 0x21, 0x00, 0xa8, 0x4c, 0x00, 0x01, 0x2c, 0x4e, 0x80, 0x00, 0x20, 0x7e, 0x23, 0x20, 0x50,
    0x3c, 0xa0, 0x48, 0x00, 0x52, 0x25, 0x01, 0xba, 0x90, 0xa3, 0x00, 0x00, 0x7c, 0x00, 0x18, 0xac,
    0x7c, 0x00, 0x04, 0xac, 0x7c, 0x00, 0x1f, 0xac, 0x4c, 0x00, 0x01, 0x2c, 0x4e, 0x80, 0x00, 0x20,
    0x7d, 0x70, 0x8b, 0xd7, 0x7d, 0x4b, 0x89, 0xd6, 0x7d, 0x4a, 0x80, 0x50, 0x91, 0x5b, 0x00, 0x00,
    0x4e, 0x80, 0x00, 0x20, 0x7f, 0xa8, 0x02, 0xa6, 0x3d, 0xe0, 0x80, 0x00, 0x61, 0xef, 0x28, 0xb8,
    0x63, 0xe7, 0x18, 0x08, 0x3c, 0xc0, 0x80, 0x00, 0x7c, 0xd0, 0x33, 0x78, 0x39, 0x00, 0x00, 0x00,
    0x3c, 0x60, 0x00, 0xd0, 0x60, 0x63, 0xc0, 0xde, 0x80, 0x8f, 0x00, 0x00, 0x7c, 0x03, 0x20, 0x00,
    0x40, 0x82, 0x00, 0x18, 0x80, 0x8f, 0x00, 0x04, 0x7c, 0x03, 0x20, 0x00, 0x40, 0x82, 0x00, 0x0c,
    0x39, 0xef, 0x00, 0x08, 0x48, 0x00, 0x00, 0x0c, 0x7f, 0xa8, 0x03, 0xa6, 0x4e, 0x80, 0x00, 0x20,
    0x80, 0x6f, 0x00, 0x00, 0x80, 0x8f, 0x00, 0x04, 0x39, 0xef, 0x00, 0x08, 0x71, 0x09, 0x00, 0x01,
    0x2f, 0x89, 0x00, 0x00, 0x39, 0x20, 0x00, 0x00, 0x54, 0x6a, 0x1f, 0x7e, 0x54, 0x65, 0x3f, 0x7e,
    0x74, 0x6b, 0x10, 0x00, 0x54, 0x63, 0x01, 0xfe, 0x40, 0x82, 0x00, 0x0c, 0x54, 0xcc, 0x00, 0x0c,
    0x48, 0x00, 0x00, 0x08, 0x7e, 0x0c, 0x83, 0x78, 0x2e, 0x05, 0x00, 0x00, 0x2c, 0x0a, 0x00, 0x01,
    0x41, 0xa0, 0x00, 0x2c, 0x41, 0xa2, 0x00, 0xe4, 0x2c, 0x0a, 0x00, 0x03, 0x41, 0xa0, 0x01, 0xac,
    0x41, 0x82, 0x02, 0x50, 0x2c, 0x0a, 0x00, 0x05, 0x41, 0x80, 0x02, 0xd4, 0x41, 0xa2, 0x04, 0xe0,
    0x2c, 0x0a, 0x00, 0x07, 0x41, 0xa0, 0x05, 0x0c, 0x48, 0x00, 0x05, 0xf0, 0x7d, 0x8c, 0x1a, 0x14,
    0x2c, 0x05, 0x00, 0x03, 0x41, 0x82, 0x00, 0x48, 0x41, 0x81, 0x00, 0x60, 0x40, 0xbe, 0xff, 0x84,
    0x2e, 0x05, 0x00, 0x01, 0x41, 0x91, 0x00, 0x2c, 0x54, 0x8a, 0x84, 0x3e, 0x41, 0x92, 0x00, 0x10,
    0x7c, 0x89, 0x61, 0xae, 0x39, 0x29, 0x00, 0x01, 0x48, 0x00, 0x00, 0x0c, 0x7c, 0x89, 0x63, 0x2e,
    0x39, 0x29, 0x00, 0x02, 0x35, 0x4a, 0xff, 0xff, 0x40, 0xa0, 0xff, 0xe4, 0x4b, 0xff, 0xff, 0x54,
    0x55, 0x8c, 0x00, 0x3a, 0x90, 0x8c, 0x00, 0x00, 0x4b, 0xff, 0xff, 0x48, 0x7c, 0x89, 0x23, 0x78,
    0x40, 0x9e, 0x04, 0xc8, 0x35, 0x29, 0xff, 0xff, 0x41, 0x80, 0x04, 0xc0, 0x7c, 0xa9, 0x78, 0xae,
    0x7c, 0xa9, 0x61, 0xae, 0x4b, 0xff, 0xff, 0xf0, 0x39, 0xef, 0x00, 0x08, 0x40, 0xbe, 0xff, 0x24,
    0x80, 0xaf, 0xff, 0xf8, 0x81, 0x6f, 0xff, 0xfc, 0x54, 0xb1, 0x04, 0x3e, 0x54, 0xaa, 0x85, 0x3e,
    0x54, 0xa5, 0x27, 0x3e, 0x2e, 0x85, 0x00, 0x01, 0x41, 0x96, 0x00, 0x10, 0x41, 0xb5, 0x00, 0x14,
    0x7c, 0x89, 0x61, 0xae, 0x48, 0x00, 0x00, 0x10, 0x7c, 0x89, 0x63, 0x2e, 0x48, 0x00, 0x00, 0x08,
    0x7c, 0x89, 0x61, 0x2e, 0x7c, 0x84, 0x5a, 0x14, 0x7d, 0x29, 0x8a, 0x14, 0x35, 0x4a, 0xff, 0xff,
    0x40, 0x80, 0xff, 0xd4, 0x4b, 0xff, 0xfe, 0xdc, 0x54, 0x69, 0x07, 0xff, 0x41, 0x82, 0x00, 0x10,
    0x55, 0x08, 0xf8, 0x7e, 0x71, 0x09, 0x00, 0x01, 0x2f, 0x89, 0x00, 0x00, 0x2e, 0x85, 0x00, 0x04,
    0x2d, 0x8a, 0x00, 0x05, 0x51, 0x08, 0x08, 0x3c, 0x40, 0x9e, 0x00, 0x78, 0x41, 0x8d, 0x04, 0xb8,
    0x7d, 0x8c, 0x1a, 0x14, 0x41, 0x8c, 0x00, 0x0c, 0x41, 0x94, 0x00, 0x30, 0x48, 0x00, 0x00, 0x1c,
    0x40, 0x94, 0x00, 0x10, 0x55, 0x8c, 0x00, 0x3a, 0x81, 0x6c, 0x00, 0x00, 0x48, 0x00, 0x00, 0x1c,
    0x55, 0x8c, 0x00, 0x3c, 0xa1, 0x6c, 0x00, 0x00, 0x7c, 0x89, 0x20, 0xf8, 0x55, 0x29, 0x84, 0x3e,
    0x7d, 0x6b, 0x48, 0x38, 0x54, 0x84, 0x04, 0x3e, 0x7f, 0x0b, 0x20, 0x40, 0x70, 0xa9, 0x00, 0x03,
    0x41, 0x82, 0x00, 0x18, 0x2c, 0x09, 0x00, 0x02, 0x41, 0x82, 0x00, 0x18, 0x41, 0x81, 0x00, 0x1c,
    0x40, 0x9a, 0x00, 0x20, 0x48, 0x00, 0x00, 0x18, 0x41, 0x9a, 0x00, 0x18, 0x48, 0x00, 0x00, 0x10,
    0x41, 0x99, 0x00, 0x10, 0x48, 0x00, 0x00, 0x08, 0x41, 0x98, 0x00, 0x08, 0x61, 0x08, 0x00, 0x01,
    0x40, 0x8e, 0xfe, 0x40, 0x41, 0x94, 0xfe, 0x3c, 0x81, 0x6f, 0xff, 0xf8, 0x40, 0x9e, 0x00, 0x20,
    0x70, 0x6c, 0x00, 0x08, 0x41, 0x82, 0x00, 0x0c, 0x71, 0x0c, 0x00, 0x01, 0x41, 0x82, 0x00, 0x10,
    0x39, 0x8b, 0x00, 0x10, 0x51, 0x8b, 0x03, 0x36, 0x48, 0x00, 0x00, 0x08, 0x55, 0x6b, 0x07, 0x16,
    0x91, 0x6f, 0xff, 0xf8, 0x4b, 0xff, 0xfe, 0x0c, 0x40, 0xbe, 0xfe, 0x08, 0x54, 0x69, 0x16, 0xba,
    0x54, 0x6e, 0x87, 0xfe, 0x2d, 0x8e, 0x00, 0x00, 0x2e, 0x05, 0x00, 0x04, 0x70, 0xae, 0x00, 0x03,
    0x2e, 0x8e, 0x00, 0x02, 0x41, 0x94, 0x00, 0x14, 0x41, 0x96, 0x00, 0x50, 0x7c, 0x64, 0x07, 0x34,
    0x7c, 0x84, 0x7a, 0x14, 0x48, 0x00, 0x00, 0x68, 0x54, 0x65, 0xa7, 0xff, 0x41, 0x82, 0x00, 0x0c,
    0x7d, 0x27, 0x48, 0x2e, 0x7c, 0x84, 0x4a, 0x14, 0x41, 0x8e, 0x00, 0x08, 0x7c, 0x8c, 0x22, 0x14,
    0x2e, 0x8e, 0x00, 0x01, 0x41, 0x96, 0x00, 0x08, 0x80, 0x84, 0x00, 0x00, 0x54, 0x63, 0x67, 0xff,
    0x41, 0x82, 0x00, 0x3c, 0x40, 0x90, 0x00, 0x0c, 0x7c, 0x84, 0x32, 0x14, 0x48, 0x00, 0x00, 0x30,
    0x7c, 0x84, 0x82, 0x14, 0x48, 0x00, 0x00, 0x28, 0x54, 0x65, 0xa7, 0xff, 0x41, 0x82, 0x00, 0x0c,
    0x7d, 0x27, 0x48, 0x2e, 0x7c, 0x84, 0x4a, 0x14, 0x40, 0x90, 0x00, 0x0c, 0x7c, 0xcc, 0x21, 0x2e,
    0x4b, 0xff, 0xfd, 0x80, 0x7e, 0x0c, 0x21, 0x2e, 0x4b, 0xff, 0xfd, 0x78, 0x40, 0x90, 0x00, 0x0c,
    0x7c, 0x86, 0x23, 0x78, 0x4b, 0xff, 0xfd, 0x6c, 0x7c, 0x90, 0x23, 0x78, 0x4b, 0xff, 0xfd, 0x64,
    0x54, 0x89, 0x1e, 0x78, 0x39, 0x29, 0x00, 0x40, 0x2c, 0x05, 0x00, 0x02, 0x41, 0x80, 0x00, 0x48,
    0x54, 0x6b, 0x50, 0x03, 0x41, 0x82, 0x00, 0x14, 0x41, 0x81, 0x00, 0x08, 0x48, 0x00, 0x00, 0x10,
    0x41, 0xbe, 0xfd, 0x40, 0x48, 0x00, 0x00, 0x08, 0x40, 0xbe, 0xfd, 0x38, 0x2c, 0x05, 0x00, 0x03,
    0x41, 0x81, 0x00, 0x10, 0x41, 0xa2, 0x00, 0x10, 0x7d, 0xe7, 0x48, 0x2e, 0x4b, 0xff, 0xfd, 0x24,
    0x7d, 0xe7, 0x49, 0x2e, 0x7c, 0x64, 0x07, 0x34, 0x54, 0x84, 0x1a, 0x78, 0x7d, 0xef, 0x22, 0x14,
    0x4b, 0xff, 0xfd, 0x10, 0x40, 0xbe, 0xfd, 0x0c, 0x7c, 0xa7, 0x4a, 0x14, 0x40, 0x92, 0x00, 0x14,
    0x54, 0x64, 0x04, 0x3e, 0x91, 0xe5, 0x00, 0x00, 0x90, 0x85, 0x00, 0x04, 0x4b, 0xff, 0xfc, 0xf4,
    0x81, 0x25, 0x00, 0x04, 0x2c, 0x09, 0x00, 0x00, 0x41, 0xa2, 0xfc, 0xe8, 0x39, 0x29, 0xff, 0xff,
    0x91, 0x25, 0x00, 0x04, 0x81, 0xe5, 0x00, 0x00, 0x4b, 0xff, 0xfc, 0xd8, 0x40, 0xbe, 0xfc, 0xd4,
    0x54, 0x6b, 0x16, 0xba, 0x7f, 0x47, 0x5a, 0x14, 0x81, 0x3a, 0x00, 0x00, 0x54, 0x6e, 0x67, 0xbe,
    0x41, 0x92, 0x00, 0x84, 0x2e, 0x05, 0x00, 0x05, 0x40, 0x90, 0x01, 0x74, 0x2e, 0x05, 0x00, 0x03,
    0x40, 0x90, 0x00, 0x90, 0x2e, 0x05, 0x00, 0x01, 0x54, 0x65, 0x87, 0xff, 0x41, 0x82, 0x00, 0x08,
    0x7c, 0x8c, 0x22, 0x14, 0x2f, 0x0e, 0x00, 0x01, 0x40, 0x92, 0x00, 0x24, 0x41, 0xb9, 0x00, 0x18,
    0x41, 0x9a, 0x00, 0x0c, 0x88, 0x84, 0x00, 0x00, 0x48, 0x00, 0x00, 0xf8, 0xa0, 0x84, 0x00, 0x00,
    0x48, 0x00, 0x00, 0xf0, 0x80, 0x84, 0x00, 0x00, 0x48, 0x00, 0x00, 0xe8, 0x54, 0x73, 0xe5, 0x3e,
    0x41, 0xb9, 0x00, 0x20, 0x41, 0x9a, 0x00, 0x10, 0x99, 0x24, 0x00, 0x00, 0x38, 0x84, 0x00, 0x01,
    0x48, 0x00, 0x00, 0x18, 0xb1, 0x24, 0x00, 0x00, 0x38, 0x84, 0x00, 0x02, 0x48, 0x00, 0x00, 0x0c,
    0x91, 0x24, 0x00, 0x00, 0x38, 0x84, 0x00, 0x04, 0x36, 0x73, 0xff, 0xff, 0x40, 0x80, 0xff, 0xd4,
    0x4b, 0xff, 0xfc, 0x40, 0x54, 0x65, 0x87, 0xff, 0x41, 0x82, 0x00, 0x08, 0x7c, 0x84, 0x62, 0x14,
    0x71, 0xc5, 0x00, 0x01, 0x41, 0x82, 0x00, 0x9c, 0x7c, 0x84, 0x4a, 0x14, 0x48, 0x00, 0x00, 0x94,
    0x54, 0x6a, 0x87, 0xbe, 0x54, 0x8e, 0x16, 0xba, 0x7e, 0x67, 0x72, 0x14, 0x40, 0x92, 0x00, 0x08,
    0x3a, 0x6f, 0xff, 0xfc, 0x80, 0x9a, 0x00, 0x00, 0x81, 0x33, 0x00, 0x00, 0x71, 0x4b, 0x00, 0x01,
    0x41, 0x82, 0x00, 0x08, 0x7c, 0x9a, 0x23, 0x78, 0x71, 0x4b, 0x00, 0x02, 0x41, 0x82, 0x00, 0x10,
    0x7d, 0x33, 0x4b, 0x78, 0x40, 0xb2, 0x00, 0x08, 0x7e, 0x6c, 0x9a, 0x14, 0x54, 0x65, 0x67, 0x3f,
    0x2c, 0x05, 0x00, 0x09, 0x40, 0x80, 0x00, 0x54, 0x48, 0x00, 0x00, 0x79, 0x7c, 0x89, 0x22, 0x14,
    0x48, 0x00, 0x00, 0x40, 0x7c, 0x89, 0x21, 0xd6, 0x48, 0x00, 0x00, 0x38, 0x7d, 0x24, 0x23, 0x78,
    0x48, 0x00, 0x00, 0x30, 0x7d, 0x24, 0x20, 0x38, 0x48, 0x00, 0x00, 0x28, 0x7d, 0x24, 0x22, 0x78,
    0x48, 0x00, 0x00, 0x20, 0x7d, 0x24, 0x20, 0x30, 0x48, 0x00, 0x00, 0x18, 0x7d, 0x24, 0x24, 0x30,
    0x48, 0x00, 0x00, 0x10, 0x5d, 0x24, 0x20, 0x3e, 0x48, 0x00, 0x00, 0x08, 0x7d, 0x24, 0x26, 0x30,
    0x90, 0x9a, 0x00, 0x00, 0x4b, 0xff, 0xfb, 0x8c, 0x2c, 0x05, 0x00, 0x0a, 0x41, 0x81, 0xfb, 0x84,
    0xc0, 0x5a, 0x00, 0x00, 0xc0, 0x73, 0x00, 0x00, 0x41, 0x82, 0x00, 0x0c, 0xec, 0x43, 0x10, 0x2a,
    0x48, 0x00, 0x00, 0x08, 0xec, 0x43, 0x00, 0xb2, 0xd0, 0x5a, 0x00, 0x00, 0x4b, 0xff, 0xfb, 0x64,
    0x7d, 0x48, 0x02, 0xa6, 0x54, 0xa5, 0x1e, 0x78, 0x7d, 0x4a, 0x2a, 0x14, 0x80, 0x9a, 0x00, 0x00,
    0x81, 0x33, 0x00, 0x00, 0x7d, 0x48, 0x03, 0xa6, 0x4e, 0x80, 0x00, 0x20, 0x40, 0xbe, 0xfb, 0x44,
    0x54, 0x69, 0xc0, 0x3e, 0x7d, 0x8e, 0x63, 0x78, 0x48, 0x00, 0x00, 0x35, 0x41, 0x92, 0x00, 0x0c,
    0x7e, 0x31, 0x22, 0x14, 0x48, 0x00, 0x00, 0x08, 0x7d, 0x29, 0x22, 0x14, 0x54, 0x64, 0xc4, 0x3f,
    0x38, 0xa0, 0x00, 0x00, 0x41, 0x82, 0xfb, 0x1c, 0x7d, 0x45, 0x88, 0xae, 0x7d, 0x45, 0x49, 0xae,
    0x38, 0xa5, 0x00, 0x01, 0x7c, 0x05, 0x20, 0x00, 0x4b, 0xff, 0xff, 0xec, 0x2e, 0x8a, 0x00, 0x04,
    0x55, 0x31, 0x36, 0xba, 0x2c, 0x11, 0x00, 0x3c, 0x7e, 0x27, 0x88, 0x2e, 0x40, 0x82, 0x00, 0x08,
    0x7d, 0xd1, 0x73, 0x78, 0x41, 0x96, 0x00, 0x08, 0xa2, 0x31, 0x00, 0x00, 0x55, 0x29, 0x56, 0xba,
    0x2c, 0x09, 0x00, 0x3c, 0x7d, 0x27, 0x48, 0x2e, 0x40, 0x82, 0x00, 0x08, 0x7d, 0xc9, 0x73, 0x78,
    0x41, 0x96, 0x00, 0x08, 0xa1, 0x29, 0x00, 0x00, 0x4e, 0x80, 0x00, 0x20, 0x2c, 0x05, 0x00, 0x04,
    0x40, 0x80, 0x00, 0x28, 0x7c, 0x89, 0x23, 0x78, 0x7d, 0xc3, 0x62, 0x14, 0x55, 0xce, 0x00, 0x3c,
    0x4b, 0xff, 0xff, 0xad, 0x7c, 0x84, 0x20, 0xf8, 0x54, 0x84, 0x04, 0x3e, 0x7d, 0x2b, 0x20, 0x38,
    0x7e, 0x24, 0x20, 0x38, 0x4b, 0xff, 0xfb, 0xc4, 0x54, 0x6b, 0xe4, 0x3e, 0x4b, 0xff, 0xfb, 0xbc,
    0x7c, 0x9a, 0x23, 0x78, 0x54, 0x84, 0x18, 0x38, 0x40, 0x92, 0x00, 0x20, 0x40, 0x9e, 0x00, 0x0c,
    0x7d, 0xe8, 0x03, 0xa6, 0x4e, 0x80, 0x00, 0x21, 0x7d, 0xe4, 0x7a, 0x14, 0x39, 0xef, 0x00, 0x07,
    0x55, 0xef, 0x00, 0x38, 0x4b, 0xff, 0xfa, 0x6c, 0x2e, 0x05, 0x00, 0x03, 0x41, 0x91, 0x00, 0x5c,
    0x3c, 0xa0, 0x48, 0x00, 0x7d, 0x83, 0x62, 0x14, 0x55, 0x8c, 0x00, 0x3a, 0x40, 0x92, 0x00, 0x20,
    0x40, 0xbe, 0xfa, 0x50, 0x57, 0x44, 0x00, 0x3a, 0x7c, 0x8c, 0x20, 0x50, 0x50, 0x85, 0x01, 0xba,
    0x50, 0x65, 0x07, 0xfe, 0x90, 0xac, 0x00, 0x00, 0x4b, 0xff, 0xfa, 0x38, 0x40, 0xbe, 0xff, 0xbc,
    0x7d, 0x2c, 0x78, 0x50, 0x51, 0x25, 0x01, 0xba, 0x90, 0xac, 0x00, 0x00, 0x39, 0x8c, 0x00, 0x04,
    0x7d, 0x6f, 0x22, 0x14, 0x39, 0x6b, 0xff, 0xfc, 0x7d, 0x2b, 0x60, 0x50, 0x51, 0x25, 0x01, 0xba,
    0x90, 0xab, 0x00, 0x00, 0x4b, 0xff, 0xff, 0x94, 0x2e, 0x05, 0x00, 0x06, 0x41, 0x92, 0x00, 0x28,
    0x4b, 0xff, 0xfb, 0x28, 0x55, 0x8c, 0x84, 0x3e, 0x57, 0x44, 0x84, 0x3e, 0x57, 0x5a, 0x04, 0x3e,
    0x7c, 0x0c, 0x20, 0x00, 0x41, 0x80, 0xfb, 0xa8, 0x7c, 0x0c, 0xd0, 0x00, 0x40, 0x80, 0xfb, 0xa0,
    0x4b, 0xff, 0xf9, 0xe0, 0x57, 0x45, 0xff, 0xfe, 0x68, 0xa5, 0x00, 0x01, 0x71, 0x03, 0x00, 0x01,
    0x7c, 0x05, 0x18, 0x00, 0x41, 0x82, 0x00, 0x1c, 0x51, 0x1a, 0x0f, 0xbc, 0x6b, 0x5a, 0x00, 0x02,
    0x57, 0x45, 0xff, 0xff, 0x41, 0x82, 0x00, 0x08, 0x6b, 0x5a, 0x00, 0x01, 0x93, 0x4f, 0xff, 0xfc,
    0x53, 0x48, 0x07, 0xfe, 0x4b, 0xff, 0xf9, 0xac, 0x2c, 0x0b, 0x00, 0x00, 0x41, 0x82, 0x01, 0x38,
    0x2c, 0x05, 0x00, 0x01, 0x41, 0x82, 0x00, 0x18, 0x2c, 0x05, 0x00, 0x02, 0x41, 0x82, 0x00, 0x14,
    0x2c, 0x05, 0x00, 0x03, 0x41, 0x82, 0x00, 0x70, 0x4b, 0xff, 0xf9, 0x80, 0x54, 0xcc, 0x00, 0x0c,
    0x54, 0x97, 0x46, 0x3e, 0x54, 0x98, 0xc4, 0x3e, 0x54, 0x84, 0x06, 0x3e, 0x40, 0x9e, 0x00, 0xfc,
    0x56, 0xf9, 0x06, 0x31, 0x7d, 0x9a, 0x63, 0x78, 0x7f, 0x43, 0xd2, 0x14, 0x57, 0x5a, 0x00, 0x3a,
    0x41, 0x82, 0x00, 0x18, 0x7e, 0xf7, 0x07, 0x74, 0x7e, 0xf7, 0x00, 0xd0, 0x1f, 0x37, 0x00, 0x02,
    0x3b, 0x39, 0x00, 0x04, 0x7f, 0x59, 0xd0, 0x50, 0x2c, 0x17, 0x00, 0x00, 0x41, 0x82, 0x00, 0x1c,
    0x3b, 0x20, 0x00, 0x00, 0x7e, 0xe9, 0x03, 0xa6, 0xa3, 0x7a, 0x00, 0x04, 0x7f, 0x79, 0xca, 0x78,
    0x3b, 0x5a, 0x00, 0x02, 0x42, 0x00, 0xff, 0xf4, 0x7c, 0x18, 0xc8, 0x00, 0x40, 0x82, 0x00, 0xac,
    0x4b, 0xff, 0xfe, 0x90, 0x51, 0x08, 0x08, 0x3c, 0x40, 0x9e, 0x00, 0x9c, 0x54, 0x77, 0xb0, 0x03,
    0x41, 0x81, 0x00, 0x88, 0x41, 0x80, 0x00, 0x8c, 0x54, 0x7e, 0x06, 0x3e, 0x1f, 0xde, 0x00, 0x02,
    0x54, 0x97, 0x00, 0x1e, 0x6e, 0xf8, 0x80, 0x00, 0x2c, 0x18, 0x00, 0x00, 0x40, 0x82, 0x00, 0x08,
    0x62, 0xf7, 0x30, 0x00, 0x54, 0x98, 0x80, 0x1e, 0x1f, 0x3e, 0x00, 0x04, 0x7f, 0x19, 0xc0, 0x50,
    0x3b, 0x20, 0x00, 0x00, 0x1f, 0x59, 0x00, 0x04, 0x7f, 0x6f, 0xd0, 0x2e, 0x7f, 0x57, 0xd0, 0x2e,
    0x3b, 0x39, 0x00, 0x01, 0x7c, 0x17, 0xc0, 0x40, 0x41, 0x81, 0x00, 0x34, 0x7c, 0x19, 0xf0, 0x00,
    0x41, 0x81, 0x00, 0x14, 0x7c, 0x1a, 0xd8, 0x00, 0x41, 0x82, 0xff, 0xdc, 0x3a, 0xf7, 0x00, 0x04,
    0x4b, 0xff, 0xff, 0xd0, 0x80, 0x6f, 0xff, 0xf8, 0x60, 0x63, 0x03, 0x00, 0x90, 0x6f, 0xff, 0xf8,
    0x92, 0xef, 0xff, 0xfc, 0x7e, 0xf0, 0xbb, 0x78, 0x48, 0x00, 0x00, 0x1c, 0x80, 0x6f, 0xff, 0xf8,
    0x60, 0x63, 0x01, 0x00, 0x90, 0x6f, 0xff, 0xf8, 0x61, 0x08, 0x00, 0x01, 0x48, 0x00, 0x00, 0x08,
    0x7c, 0x90, 0x23, 0x78, 0x54, 0x64, 0x06, 0x3e, 0x1c, 0x84, 0x00, 0x08, 0x7d, 0xe4, 0x7a, 0x14,
    0x4b, 0xff, 0xf8, 0x70, 0x40, 0x92, 0x00, 0x0c, 0x39, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x14,
    0x54, 0x69, 0x06, 0xff, 0x54, 0x65, 0x67, 0xfe, 0x7d, 0x08, 0x4c, 0x30, 0x55, 0x17, 0xff, 0xff,
    0x40, 0x82, 0x00, 0x08, 0x7d, 0x08, 0x2a, 0x78, 0x54, 0x85, 0x00, 0x1f, 0x41, 0x82, 0x00, 0x08,
    0x7c, 0xa6, 0x2b, 0x78, 0x54, 0x85, 0x80, 0x1f, 0x41, 0x82, 0x00, 0x08, 0x7c, 0xb0, 0x2b, 0x78,
    0x4b, 0xff, 0xf8, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd0, 0xc0, 0xde, 0x00, 0xd0, 0xc0, 0xde,
    0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char multidol[] = {
    0x7f, 0xe8, 0x03, 0xa6, 0x7c, 0x08, 0x02, 0xa6, 0x90, 0x01, 0x00, 0xac, 0x7c, 0x00, 0x00, 0x26,
    0x90, 0x01, 0x00, 0x0c, 0x7c, 0x09, 0x02, 0xa6, 0x90, 0x01, 0x00, 0x10, 0x7c, 0x01, 0x02, 0xa6,
    0x90, 0x01, 0x00, 0x14, 0xbc, 0x61, 0x00, 0x18, 0x3c, 0x60, 0x80, 0x00, 0x60, 0x63, 0x18, 0xa8,
    0x3c, 0xe0, 0x80, 0x00, 0x60, 0xe7, 0x11, 0x98, 0x3e, 0x60, 0x80, 0x00, 0x62, 0x73, 0x11, 0x88,
    0x3e, 0x40, 0x4e, 0x80, 0x62, 0x52, 0x00, 0x20, 0x81, 0xc7, 0x00, 0x04, 0x81, 0xe7, 0x00, 0x08,
    0x82, 0x07, 0x00, 0x0c, 0x82, 0x27, 0x00, 0x00, 0x3c, 0x80, 0x80, 0x00, 0x3c, 0xa0, 0x81, 0x33,
    0x38, 0x84, 0xff, 0xfc, 0x84, 0xc4, 0x00, 0x04, 0x7c, 0x04, 0x28, 0x00, 0x40, 0x80, 0x00, 0x4c,
    0x7c, 0x06, 0x70, 0x00, 0x40, 0x82, 0xff, 0xf0, 0x84, 0xc4, 0x00, 0x04, 0x7c, 0x06, 0x78, 0x00,
    0x40, 0x82, 0xff, 0xe0, 0x84, 0xc4, 0x00, 0x04, 0x7c, 0x06, 0x80, 0x00, 0x40, 0x82, 0xff, 0xd4,
    0x84, 0xc4, 0x00, 0x04, 0x7c, 0x06, 0x88, 0x00, 0x40, 0x82, 0xff, 0xc8, 0x84, 0xc4, 0x00, 0x04,
    0x7c, 0x04, 0x28, 0x00, 0x40, 0x80, 0x00, 0x14, 0x7c, 0x06, 0x90, 0x00, 0x40, 0x82, 0xff, 0xf0,
    0x48, 0x00, 0x00, 0xad, 0x4b, 0xff, 0xff, 0xb0, 0x3c, 0x60, 0x80, 0x00, 0x60, 0x63, 0x10, 0x00,
    0x3e, 0x60, 0x80, 0x00, 0x62, 0x73, 0x11, 0x90, 0x3c, 0xe0, 0x80, 0x00, 0x60, 0xe7, 0x11, 0xa8,
    0x81, 0xc7, 0x00, 0x04, 0x81, 0xe7, 0x00, 0x08, 0x82, 0x07, 0x00, 0x0c, 0x82, 0x27, 0x00, 0x00,
    0x3c, 0x80, 0x80, 0x00, 0x3c, 0xa0, 0x81, 0x40, 0x38, 0x84, 0xff, 0xfc, 0x84, 0xc4, 0x00, 0x04,
    0x7c, 0x04, 0x28, 0x00, 0x40, 0x80, 0x00, 0x38, 0x7c, 0x06, 0x70, 0x00, 0x40, 0x82, 0xff, 0xf0,
    0x84, 0xc4, 0x00, 0x04, 0x7c, 0x06, 0x78, 0x00, 0x40, 0x82, 0xff, 0xe0, 0x84, 0xc4, 0x00, 0x04,
    0x7c, 0x06, 0x80, 0x00, 0x40, 0x82, 0xff, 0xd4, 0x84, 0xc4, 0x00, 0x04, 0x7c, 0x06, 0x88, 0x00,
    0x40, 0x82, 0xff, 0xc8, 0x48, 0x00, 0x00, 0x39, 0x4b, 0xff, 0xff, 0xc4, 0x80, 0x01, 0x00, 0xac,
    0x7c, 0x08, 0x03, 0xa6, 0x80, 0x01, 0x00, 0x0c, 0x7c, 0x0f, 0xf1, 0x20, 0x80, 0x01, 0x00, 0x10,
    0x7c, 0x09, 0x03, 0xa6, 0x80, 0x01, 0x00, 0x14, 0x7c, 0x01, 0x03, 0xa6, 0xb8, 0x61, 0x00, 0x18,
    0x80, 0x01, 0x00, 0x08, 0x38, 0x21, 0x00, 0xa8, 0x48, 0x00, 0x07, 0x50, 0x7e, 0x44, 0x18, 0x50,
    0x3c, 0xc0, 0x48, 0x00, 0x52, 0x46, 0x01, 0xba, 0x90, 0xc4, 0x00, 0x00, 0x90, 0xd3, 0x00, 0x00,
    0x90, 0x93, 0x00, 0x04, 0x7c, 0x00, 0x20, 0xac, 0x7c, 0x00, 0x04, 0xac, 0x7c, 0x00, 0x27, 0xac,
    0x4c, 0x00, 0x01, 0x2c, 0x4e, 0x80, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0xc7, 0x00, 0x4c, 0x7c, 0xe3, 0x3b, 0x78,
    0x38, 0x87, 0x00, 0x34, 0x38, 0xa7, 0x00, 0x38, 0x4e, 0x80, 0x04, 0x20, 0x7c, 0x00, 0x04, 0xac,
    0x4c, 0x00, 0x01, 0x2c, 0x7f, 0xe9, 0x03, 0xa6
};

static void _start_gecko(void);

BSLUG_MUST_REPLACE(_start, _start_gecko);

static void _start_gecko(void) {
    memcpy((void*)0x80001800, codehandler, sizeof(codehandler));
    DCFlushRange((void*)0x80001800, sizeof(codehandler));
    memcpy((void*)0x80001000, multidol, sizeof(multidol));
    DCFlushRange((void*)0x80001000, sizeof(multidol));
    
    *hook_wii_vi =
        0x48000000 + ((0x800018A8 - (uint32_t)hook_wii_vi) & 0x3fffffc);
    DCFlushRange((void *)((uint32_t)hook_wii_vi & ~0x1f), 32);
    _start();
}
