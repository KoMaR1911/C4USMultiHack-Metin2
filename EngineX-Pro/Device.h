#pragma once
#ifdef DX9
#define DirectDevice IDirect3DDevice9*
#define DirectDevice2 LPDIRECT3DDEVICE9
#define DirectTexture LPDIRECT3DTEXTURE9
#define EndSceneIndex 42
#define ResetIndex 16
#else
#define DirectDevice IDirect3DDevice8*
#define DirectDevice2 LPDIRECT3DDEVICE8
#define DirectTexture LPDIRECT3DTEXTURE8
#define EndSceneIndex 35
#define ResetIndex 14
#endif
#include <VersionHelpers.h>
class Device
{
public:
	static DirectDevice2 pDevice;
	static LPD3DXMESH ms_lpSphereMesh;
	static LPD3DXMESH ms_lpCylinderMesh;
};
DirectDevice2 Device::pDevice = NULL;
LPD3DXMESH Device::ms_lpSphereMesh = NULL;
LPD3DXMESH Device::ms_lpCylinderMesh = NULL;
