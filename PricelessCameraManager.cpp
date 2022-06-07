// Fill out your copyright notice in the Description page of Project Settings.


#include "PricelessCameraManager.h"

void APricelessCameraManager::DoUpdateCamera(float DeltaTime)
{
	// Update the camera
	Super::DoUpdateCamera(DeltaTime);

	// Snap the final camera location to the pixel grid
	{
		// constexpr float PixelsPerUnits = 0.24f;
		// constexpr float UnitsPerPixel = 1.0f / PixelsPerUnits;
		//
		// FMinimalViewInfo CameraCachePOV = GetCameraCachePOV();
		// CameraCachePOV.Location.X = FMath::GridSnap(CameraCachePOV.Location.X, UnitsPerPixel);
		// CameraCachePOV.Location.Z = FMath::GridSnap(CameraCachePOV.Location.Z, UnitsPerPixel);
		// FillCameraCache(CameraCachePOV);
	}
}

