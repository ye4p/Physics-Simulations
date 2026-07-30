#pragma once
#include <windows.h>
#include <cstdint>
#include <iostream>

static const int W = 800;
static const int H = 800;
static int squareW = 600;
static int squareH = 600;
static uint32_t *gPixels = nullptr;
static BITMAPINFO gBmi = {};
static double maxHm = 40.0;
static double maxWm = 40.0;

void InitFramebuffer();

void ShutdownFramebuffer();

void Clear(uint32_t color);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void display();