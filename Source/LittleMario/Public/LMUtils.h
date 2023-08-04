// Little Mario Game: Course Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class LMUtils
{
public:
    LMUtils();
    ~LMUtils();
	
	template <typename T>
	static T* GetLMPlayerComponent(AActor* MainActor)
	{
          if (!MainActor) return nullptr;

		  const auto Component = MainActor->GetComponentByClass(T::StaticClass());
          return Cast<T>(Component);
	}
};
