#pragma once

#include <windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_6.h>

using Microsoft::WRL::ComPtr;

class AppWindow
{
public:
    AppWindow(HINSTANCE hInst);

    bool Create(LPCWSTR title, int width, int height);
    void Show(int nCmdShow);
    void RunMessageLoop();
    void Render();

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    void InitDirectX();
    void PopulateCommandList();

    void CreateRenderTargetViews();

private:
    HINSTANCE hInstance;
    HWND hwnd;

    ComPtr<ID3D12Device> device;
    ComPtr<ID3D12CommandQueue> commandQueue;
    ComPtr<IDXGISwapChain3> swapChain;
    ComPtr<ID3D12DescriptorHeap> rtvHeap;
    ComPtr<ID3D12Resource> renderTargets[2];
    ComPtr<ID3D12CommandAllocator> commandAllocator;
    ComPtr<ID3D12GraphicsCommandList> commandList;

    UINT rtvDescriptorSize = 0;
    UINT frameIndex = 0;
};
