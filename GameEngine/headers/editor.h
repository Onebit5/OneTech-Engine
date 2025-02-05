#pragma once

#ifndef EDITOR_H
#define EDITOR_H

#include "level.h"
#include "graphics.h"
#include "utils.h"

int is_editor_mode();
void toggle_editor_mode();
void render_grid(uint8_t* buffer, const Level* level);

#endif 
