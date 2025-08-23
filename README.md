# FirstModule

## A Complete Guide to Creating and Managing UE5 Modules

<!-- Banner Image Placeholder -->
![Project Banner](./banner.png)
<!-- You can add your project banner image here -->

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-0E1128?style=for-the-badge&logo=unrealengine&logoColor=white)
![Version](https://img.shields.io/badge/UE%20Version-5.6.1-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-Apache%202.0-green?style=for-the-badge)
![Build Status](https://img.shields.io/badge/Build-Passing-brightgreen?style=for-the-badge)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D4?style=for-the-badge&logo=windows&logoColor=white)

---

## Table of Contents
1. [What is an Unreal Module](#what-is-an-unreal-module)
2. [Module Structure Analysis](#module-structure-analysis)
3. [Creating Modules Manually](#creating-modules-manually)
4. [Creating Modules with IDE](#creating-modules-with-ide)
5. [Module Dependencies](#module-dependencies)
6. [Best Practices](#best-practices)
7. [Common Issues and Solutions](#common-issues-and-solutions)

## What is an Unreal Module

An Unreal Engine Module is the fundamental unit of code organization, similar to Libraries or Packages in other programming languages. Each module is an independent compilation unit with the following characteristics:

- **Encapsulation**: Groups related functionality together
- **Reusability**: Can be shared across different projects
- **Dependency Management**: Clearly defines dependencies between modules
- **Load Control**: Controls when and how modules are loaded

## Module Structure Analysis

### Standard Unreal Module Structure

```
Source/
└── [ModuleName]/
    ├── [ModuleName].Build.cs       # Build configuration file
    ├── Public/                     # Public header files
    │   ├── [ModuleName]Module.h    # Main module header
    │   └── [PublicClass].h         # Other public classes
    └── Private/                    # Private implementation files
        ├── [ModuleName]Module.cpp  # Module implementation
        └── [PrivateClass].cpp      # Other implementation files
```

### Real Project Structure (FirstModule)

> **📝 Important Note:** 
> The module names **Auto** and **Manual** in this project are chosen purely to demonstrate two different methods of module creation:
> - **Auto**: Created using IDE (JetBrains Rider) with automatic generation
> - **Manual**: Created manually with full control over the process
> 
> These names have **no special meaning** regarding module dependencies or functionality. The same principles apply to any module names (e.g., ModuleA/ModuleB, GameplayCore/UISystem, etc.). The dependency relationship (Manual depends on Auto) is simply for demonstration purposes and could easily be reversed or applied to any other module combination.

```
FirstModule/Source/
├── Auto/                       # IDE-created module
│   ├── Auto.Build.cs
│   ├── Public/
│   │   ├── AutoModule.h
│   │   ├── AutoCppOnly.h
│   │   └── AutoExposed.h
│   └── Private/
│       ├── AutoModule.cpp
│       ├── AutoCppOnly.cpp
│       ├── AutoExposed.cpp
│       ├── AutoInternal.cpp
│       └── AutoInternal.h
├── Manual/                     # Manually created module
│   ├── Manual.Build.cs
│   ├── Public/
│   │   ├── ManualModule.h
│   │   ├── ManualCppOnly.h     # C++ only classes
│   │   └── ManualExposed.h     # Blueprint compatible
│   └── Private/
│       ├── ManualModule.cpp
│       ├── ManualCppOnly.cpp
│       ├── ManualExposed.cpp
│       ├── ManualInternal.cpp
│       └── ManualInternal.h    # Internal implementation
└── FirstModule/                # Main game module
    ├── FirstModule.Build.cs
    ├── FirstModule.cpp
    └── FirstModule.h
```

### Core Files Explanation

1. **Build.cs File**: Defines compilation settings and dependencies
2. **Module.h File**: Public interface definition of the module
3. **Module.cpp File**: Actual implementation of the module
4. **Public Folder**: Header files for use by other modules
5. **Private Folder**: Internal implementation files for the module

## Creating Modules Manually

Let's examine how the **Manual** module was created in this project:

### Step 1: Create Directory Structure

Create a new module folder under the `Source/` directory:

```
Source/
└── Manual/
    ├── Public/
    └── Private/
```

### Step 2: Create Build.cs File

Create `Source/Manual/Manual.Build.cs`:

```csharp
//----------------------------------------------------------------------------------------------------
// Manual.Build.cs
//----------------------------------------------------------------------------------------------------

using UnrealBuildTool;

public class Manual : ModuleRules
{
	public Manual(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange([
			"Core",
			"Auto"  // This module depends on Auto module
		]);

		PrivateDependencyModuleNames.AddRange([
			"CoreUObject",
			"Engine"
		]);
	}
}
```

### Step 3: Create Module Header File

Create `Source/Manual/Public/ManualModule.h`:

```cpp
//----------------------------------------------------------------------------------------------------
// ManualModule.h
//----------------------------------------------------------------------------------------------------

#pragma once

#include <CoreMinimal.h>
#include <Modules/ModuleManager.h>

DECLARE_LOG_CATEGORY_EXTERN(LogManual, Log, All);

class MANUAL_API FManualModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
```

### Step 4: Create Module Implementation File

Create `Source/Manual/Private/ManualModule.cpp`:

```cpp
//----------------------------------------------------------------------------------------------------
// ManualModule.cpp
//----------------------------------------------------------------------------------------------------

#include "ManualModule.h"
#include <Modules/ModuleManager.h>

DEFINE_LOG_CATEGORY(LogManual);

#define LOCTEXT_NAMESPACE "FManualModule"

void FManualModule::StartupModule()
{
    UE_LOG(LogManual, Warning, TEXT("FManualModule::StartupModule()"));
}

void FManualModule::ShutdownModule()
{
    UE_LOG(LogManual, Warning, TEXT("FManualModule::ShutdownModule()"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FManualModule, Manual)
```

### Step 5: Register Module to Project

**FirstModule.uproject:**
```json
{
  "FileVersion": 3,
  "EngineAssociation": "5.6",
  "Modules": [
    {
      "Name": "FirstModule",
      "Type": "Runtime",
      "LoadingPhase": "Default"
    },
    {
      "Name": "Auto",
      "Type": "Runtime",
      "LoadingPhase": "Default"
    },
    {
      "Name": "Manual",
      "Type": "Runtime",
      "LoadingPhase": "Default"
    }
  ]
}
```

**FirstModule.Target.cs:**
```csharp
//----------------------------------------------------------------------------------------------------
// FirstModule.Target.cs
//----------------------------------------------------------------------------------------------------

using UnrealBuildTool;

public class FirstModuleTarget : TargetRules
{
	public FirstModuleTarget(TargetInfo Target) : base(Target)
	{
		Type                 = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion  = EngineIncludeOrderVersion.Unreal5_6;
		ExtraModuleNames.Add("FirstModule");
		RegisterModulesCreatedByRider();
	}

	private void RegisterModulesCreatedByRider()
	{
		ExtraModuleNames.AddRange(["Auto", "Manual"]);
	}
}
```

### Generic Template for Any Module

For creating your own modules, use this template:

```csharp
// YourModuleName.Build.cs
using UnrealBuildTool;

public class YourModuleName : ModuleRules
{
    public YourModuleName(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange([
            "Core"
        ]);

        PrivateDependencyModuleNames.AddRange([
            "CoreUObject",
            "Engine"
        ]);
    }
}
```

## Creating Modules with IDE

### JetBrains Rider

The **Auto** module in this project was created using Rider:

1. **Right-click on the project root directory** → Select "Add" → "New Unreal Module"
2. **Enter module name**: "Auto"
3. **Select module type**: Runtime
4. **Select loading phase**: Default
5. **Click Confirm**, Rider automatically created:

```csharp
//----------------------------------------------------------------------------------------------------
// Auto.Build.cs (Generated by Rider)
//----------------------------------------------------------------------------------------------------

using UnrealBuildTool;

public class Auto : ModuleRules
{
    public Auto(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange([
            "Core"
        ]);

        PrivateDependencyModuleNames.AddRange([
            "CoreUObject",
            "Engine"
        ]);
    }
}
```

```cpp
//----------------------------------------------------------------------------------------------------
// AutoModule.h (Generated by Rider)
//----------------------------------------------------------------------------------------------------

#pragma once

#include <CoreMinimal.h>
#include <Modules/ModuleManager.h>

DECLARE_LOG_CATEGORY_EXTERN(LogAuto, Log, All);

class FAutoModule final : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
```

```cpp
//----------------------------------------------------------------------------------------------------
// AutoModule.cpp (Generated by Rider)
//----------------------------------------------------------------------------------------------------

#include "AutoModule.h"
#include <Modules/ModuleManager.h>

DEFINE_LOG_CATEGORY(LogAuto);

#define LOCTEXT_NAMESPACE "FAutoModule"

void FAutoModule::StartupModule()
{
	UE_LOG(LogAuto, Warning, TEXT("FAutoModule::StartupModule()"));
}

void FAutoModule::ShutdownModule()
{
	UE_LOG(LogAuto, Warning, TEXT("FAutoModule::ShutdownModule()"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAutoModule, Auto)
```

### Visual Studio

1. **Install Unreal Engine Extension**
2. **Right-click on Solution** → "Add" → "New Project"
3. **Select Unreal Engine Module Template**
4. **Configure module settings** and finish creation

## Module Dependencies

> **📝 Naming Convention Note:**
> In this project, "Manual depends on Auto" is purely for demonstration. The dependency direction has nothing to do with how the modules were created (manually vs IDE). In real projects, you might have:
> - `GameplayCore` depends on `UtilityLibrary`
> - `UISystem` depends on `GameplayCore` 
> - `AudioManager` depends on `ConfigurationModule`
> - `PlayerController` depends on `InputManager`
> 
> The dependency direction and module names should reflect your actual project architecture, not the creation method. You could equally have:
> - Auto depends on Manual
> - ModuleA depends on ModuleB
> - Any meaningful combination based on your project needs

### Manual Module Depends on Auto Module

**Manual.Build.cs shows the dependency:**
```csharp
PublicDependencyModuleNames.AddRange([
    "Core",
    "Auto"  // Manual depends on Auto
]);
```

### Using Classes from Other Modules

**ManualExposed.h includes AutoCppOnly:**
```cpp
//----------------------------------------------------------------------------------------------------
// ManualExposed.h
//----------------------------------------------------------------------------------------------------

#pragma once

#include <CoreMinimal.h>
#include "AutoCppOnly.h"  // Include from Auto module
#include <ManualExposed.generated.h>

UCLASS(Blueprintable)
class MANUAL_API AManualExposed : public AActor
{
	GENERATED_BODY()

public:
	AManualExposed();

	UFUNCTION(BlueprintCallable, Category = "Manual")
	void DoManualExposed() const;

	FAutoCppOnly AutoCppOnly;  // Using class from Auto module
};
```

**ManualExposed.cpp uses the Auto module class:**
```cpp
//----------------------------------------------------------------------------------------------------
// ManualExposed.cpp
//----------------------------------------------------------------------------------------------------

#include "ManualExposed.h"
#include "ManualModule.h"

AManualExposed::AManualExposed()
{
	UE_LOG(LogManual, Warning, TEXT("AManualExposed::AManualExposed()"));
}

void AManualExposed::DoManualExposed() const
{
	UE_LOG(LogManual, Warning, TEXT("AManualExposed::DoManualExposed()"));
	AutoCppOnly.DoAutoCppOnly();  // Call method from Auto module
}
```

### Dependency Type Description

- **PublicDependencyModuleNames**: Public dependencies, modules that depend on this module can also use them
- **PrivateDependencyModuleNames**: Private dependencies, used only internally within this module

## Best Practices

### 1. Class Classification System (Real Implementation)

Based on this project's structure, here's the three-tier classification:

#### ManualCppOnly (C++ Only Classes)
**Purpose**: High-performance C++ API for other modules
**Features**:
- ✅ Other C++ modules can use
- ❌ Blueprint cannot inherit/call
- ⚡ High performance, no reflection system overhead

```cpp
//----------------------------------------------------------------------------------------------------
// ManualCppOnly.h
//----------------------------------------------------------------------------------------------------

#pragma once

#include <CoreMinimal.h>

class MANUAL_API FManualCppOnly
{
public:
	FManualCppOnly();
	void DoManualCppOnly();
};
```

```cpp
//----------------------------------------------------------------------------------------------------
// ManualCppOnly.cpp
//----------------------------------------------------------------------------------------------------

#include "ManualCppOnly.h"
#include "ManualModule.h"

FManualCppOnly::FManualCppOnly()
{
	UE_LOG(LogManual, Warning, TEXT("FManualCppOnly::FManualCppOnly()"));
}

void FManualCppOnly::DoManualCppOnly()
{
	UE_LOG(LogManual, Warning, TEXT("FManualCppOnly::DoManualCppOnly()"));
}
```

#### ManualExposed (Blueprint Compatible Classes)
**Purpose**: Blueprint-compatible game logic
**Features**:
- ✅ Other C++ modules can use
- ✅ Blueprint can inherit/call
- 🔄 Can internally call other module's classes (like AutoCppOnly)

```cpp
//----------------------------------------------------------------------------------------------------
// ManualExposed.h
//----------------------------------------------------------------------------------------------------

#pragma once

#include <CoreMinimal.h>
#include "AutoCppOnly.h"
#include <ManualExposed.generated.h>

UCLASS(Blueprintable)
class MANUAL_API AManualExposed : public AActor
{
	GENERATED_BODY()

public:
	AManualExposed();

	UFUNCTION(BlueprintCallable, Category = "Manual")
	void DoManualExposed() const;

	FAutoCppOnly AutoCppOnly;
};
```

#### ManualInternal (Internal Implementation)
**Purpose**: Internal module implementation details
**Features**:
- ❌ Other modules cannot use (located in Private folder)
- ❌ Blueprint cannot access
- 🔒 Encapsulates implementation details

```cpp
//----------------------------------------------------------------------------------------------------
// ManualInternal.h
//----------------------------------------------------------------------------------------------------

#pragma once
#include <CoreMinimal.h>

class FManualInternal
{
	FManualInternal();
	void DoManualInternal() const;
};
```

### 2. Naming Conventions

- **Module Names**: Use PascalCase, e.g., `Auto`, `Manual`
- **Class Names**: Use appropriate prefix:
  - `F` for regular classes: `FManualCppOnly`
  - `A` for Actors: `AManualExposed`
  - `U` for UObject-derived: `UManualComponent`
- **API Macros**: Use uppercase module name: `MANUAL_API`, `AUTO_API`

### 3. Directory Organization

```
Source/Manual/
├── Public/                   # External interface
│   ├── ManualModule.h        # Module definition
│   ├── ManualCppOnly.h       # C++ only classes
│   └── ManualExposed.h       # Blueprint compatible
└── Private/                  # Internal implementation
    ├── ManualModule.cpp      # Module implementation
    ├── ManualCppOnly.cpp     # C++ implementation
    ├── ManualExposed.cpp     # Blueprint class implementation
    ├── ManualInternal.h      # Internal definitions
    └── ManualInternal.cpp    # Internal implementation
```

### 4. API Exposure Control

```cpp
// Public class - can be used by other modules
class MANUAL_API FManualCppOnly  // Has MANUAL_API macro
{
    // Accessible from other modules
};

// Private class - internal use only
class FManualInternal  // No API macro, in Private folder
{
    // Internal use only
};
```

### 5. Log Management (Real Implementation)

```cpp
// In ManualModule.h
DECLARE_LOG_CATEGORY_EXTERN(LogManual, Log, All);

// In ManualModule.cpp
DEFINE_LOG_CATEGORY(LogManual);

// Usage throughout the module
UE_LOG(LogManual, Warning, TEXT("FManualCppOnly::DoManualCppOnly()"));
```

## Common Issues and Solutions

### Issue 1: Module Cannot Load

**Symptoms**: Game startup shows module not found

**Solutions**:
1. Check if .uproject file correctly registers the module
2. Check if Target.cs files include the module name
3. Confirm Build.cs file syntax is correct
4. Regenerate project files

### Issue 2: Compilation Errors

**Symptoms**: Cannot find header files or linking errors

**Solutions**:
1. Check dependencies in Build.cs (like Manual depending on Auto)
2. Confirm API macros are used correctly (`MANUAL_API`, `AUTO_API`)
3. Check include paths
4. Clean and rebuild

### Issue 3: Circular Dependencies

**Symptoms**: Module A depends on B, B also depends on A

**Solutions**:
1. Redesign module architecture
2. Extract common dependencies to a third module
3. Use forward declarations to reduce dependencies
4. Consider using interfaces for decoupling

### Issue 4: Blueprint Integration Issues

**Symptoms**: C++ classes not visible in Blueprint

**Solutions**:
1. Ensure class inherits from UObject/AActor/UComponent
2. Add UCLASS macro with BlueprintType, Blueprintable
3. Use UFUNCTION for callable functions
4. Use UPROPERTY for accessible properties
5. Regenerate project files after changes

**Example from ManualExposed (Working Blueprint Class):**
```cpp
UCLASS(Blueprintable)  // Makes class available in Blueprint
class MANUAL_API AManualExposed : public AActor
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Manual")  // Callable from Blueprint
    void DoManualExposed() const;
};
```

### Issue 5: Constructor Called Multiple Times

**Symptoms**: Constructor logs appear multiple times before game starts

```
LogManual: Warning: AManualExposed::AManualExposed()
LogManual: Warning: AManualExposed::AManualExposed()
LogManual: Warning: AManualExposed::AManualExposed()
```

**This is normal behavior!** UE calls constructors for:
1. **CDO (Class Default Object)** creation
2. **Blueprint asset validation**
3. **Editor preview systems**
4. **Actor Factory systems**

**Best Practices**:
- Keep constructors lightweight (only set default values)
- Put game logic in `BeginPlay()` instead
- Use `IsTemplate()` to check if it's a CDO

```cpp
AManualExposed::AManualExposed()
{
    // ✅ Good: Just log and set defaults
    UE_LOG(LogManual, Warning, TEXT("AManualExposed::AManualExposed()"));
    
    // ❌ Bad: Don't do game logic here
    // StartGameplay();
    // LoadAssets();
}

void AManualExposed::BeginPlay()
{
    Super::BeginPlay();
    // ✅ Good: Game logic goes here
    StartGameplay();
}
```

## Core Module Macros Explained

### DEFINE_LOG_CATEGORY(LogManual)
```cpp
// In ManualModule.cpp
DEFINE_LOG_CATEGORY(LogManual);
```
- **Purpose**: Creates a dedicated log category for the module
- **Usage**: `UE_LOG(LogManual, Warning, TEXT("Message"));`
- **Benefits**: Filter module-specific logs in editor

### LOCTEXT_NAMESPACE "FManualModule"
```cpp
// In ManualModule.cpp
#define LOCTEXT_NAMESPACE "FManualModule"
// ... module code ...
#undef LOCTEXT_NAMESPACE
```
- **Purpose**: Sets namespace for localization text
- **Usage**: `LOCTEXT("Key", "Default Text")`
- **Benefits**: Supports game internationalization

### IMPLEMENT_MODULE(FManualModule, Manual)
```cpp
// In ManualModule.cpp
IMPLEMENT_MODULE(FManualModule, Manual)
```
- **Purpose**: Registers module with UE system
- **Format**: `IMPLEMENT_MODULE(ClassName, ModuleName)`
- **Critical**: Without this, module won't load!

## Conclusion

This handbook is based on the real **FirstModule** project, demonstrating:

- **Auto Module**: Created using IDE (Rider) with automatic generation
- **Manual Module**: Created manually with full control over structure
- **Dependency System**: Manual depends on Auto, showing inter-module communication
- **Classification System**: CppOnly, Exposed, and Internal classes for different access levels
- **Blueprint Integration**: Real working examples of C++ to Blueprint exposure

Through proper module design, you can:
- Improve code maintainability
- Facilitate team collaboration
- Enable feature reuse
- Optimize compilation time
- Create clear separation between C++ and Blueprint functionality

Remember, good module design is the foundation of successful UE projects. Start with small modules and gradually build your modular architecture.
