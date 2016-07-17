#
# CMakeLists.txt -- build system for LuaSDL2 (SDL_ext module)
#
# Copyright (c) 2013, 2014 David Demelier <markand@malikania.fr>
# Copyright (c) 2014 Joseph Wallace <tangent128@gmail.com>
# Copyright (c) 2016 Webster Sheets <info@web-eworks.com>
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

find_package(SDL2 REQUIRED)

set(
	EXT_SOURCES
	src/ext.c
)

include_directories(
	"${LuaSDL_SOURCE_DIR}/src"
	${SDL2_INCLUDE_DIRS}
)

add_library(
	ext
	MODULE
	${EXT_SOURCES}
)

set_target_properties(
	ext
	PROPERTIES
	PREFIX ""
)

target_link_libraries(
	ext
	common
	${SDL2_LIBRARY}
)

install(
	TARGETS ext
	DESTINATION ${LUA_LIBDIR}/SDL
)
