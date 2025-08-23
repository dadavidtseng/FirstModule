# Unreal Engine Module Development Handbook

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

A standard Unreal Module has the following directory structure:

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

### Core Files Explanation

1. **Build.cs File**: Defines compilation settings and dependencies
2. **Module.h File**: Public interface definition of the module
3. **Module.cpp File**: Actual implementation of the module
4. **Public Folder**: Header files for use by other modules
5. **Private Folder**: Internal implementation files for the module

## Creating Modules Manually

### Step 1: Create Directory Structure

Create a new module folder under the `Source/` directory:

```
Source/
└── YourModuleName/
    ├── Public/
    └── Private/
```

### Step 2: Create Build.cs File

Create `Source/YourModuleName/YourModuleName.Build.cs`:

```csharp
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

### Step 3: Create Module Header File

Create `Source/YourModuleName/Public/YourModuleNameModule.h`:

```cpp
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogYourModuleName, Log, All);

class YOURMODULENAME_API FYourModuleNameModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
```

### Step 4: Create Module Implementation File

Create `Source/YourModuleName/Private/YourModuleNameModule.cpp`:

```cpp
#include "YourModuleNameModule.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogYourModuleName);

#define LOCTEXT_NAMESPACE "FYourModuleNameModule"

void FYourModuleNameModule::StartupModule()
{
    UE_LOG(LogYourModuleName, Warning, TEXT("YourModuleName module has been loaded"));
}

void FYourModuleNameModule::ShutdownModule()
{
    UE_LOG(LogYourModuleName, Warning, TEXT("YourModuleName module has been unloaded"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FYourModuleNameModule, YourModuleName)
```

### Step 5: Register Module to Project

Add the module to your `.uproject` file:

```json
{
  "Modules": [
    {
      "Name": "YourModuleName",
      "Type": "Runtime",
      "LoadingPhase": "Default"
    }
  ]
}
```

Add the module to your `Target.cs` files:

```csharp
private void RegisterModulesCreatedByRider()
{
    ExtraModuleNames.AddRange(["YourModuleName"]);
}
```

## Creating Modules with IDE

### JetBrains Rider

1. **Right-click on the project root directory** → Select "Add" → "New Unreal Module"
2. **Enter module name**: e.g., "YourModuleName"
3. **Select module type**:
   - Runtime: Runtime game module
   - Editor: Editor-only module
   - Developer: Development tool module
4. **Select loading phase**:
   - Default: Default loading
   - PostEngineInit: Load after engine initialization
   - PreDefault: Load before default
5. **Click Confirm**, Rider will automatically:
   - Create directory structure
   - Generate Build.cs file
   - Create module header and implementation files
   - Update .uproject file
   - Update Target.cs files

### Visual Studio

1. **Install Unreal Engine Extension**
2. **Right-click on Solution** → "Add" → "New Project"
3. **Select Unreal Engine Module Template**
4. **Configure module settings**:
   - Module name
   - Module type
   - Loading phase
5. **Finish creation**, Visual Studio will automatically handle all files

## Module Dependencies

### Establishing Dependencies

Add dependencies in the Build.cs file:

```csharp
public class Auto : ModuleRules
{
    public Auto(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange([
            "Core",
            "Manual"  // Depends on Manual module
        ]);
    }
}
```

### Using Classes from Other Modules

Include header files from other modules in cpp files:

```cpp
#include "Auto.h"
#include "ManualCppOnly.h"  // From Manual module

void FAutoModule::StartupModule()
{
    FManualCppOnly::ProcessLargeDataset({1.0f, 2.0f, 3.0f});
}
```

### Dependency Type Description

- **PublicDependencyModuleNames**: Public dependencies, modules that depend on this module can also use them
- **PrivateDependencyModuleNames**: Private dependencies, used only internally within this module

## Best Practices

### 1. Naming Conventions

- **Module Names**: Use PascalCase, e.g., `GameplayAbilities`
- **Class Names**: Use F prefix, e.g., `FMyModuleClass`
- **API Macros**: Use uppercase module name, e.g., `MYMODULE_API`

### 2. Directory Organization

```
Source/YourModule/
├── Public/
│   ├── YourModuleModule.h
│   ├── Core/           # Core functionality
│   ├── Components/     # Component classes
│   └── Interfaces/     # Interface definitions
└── Private/
    ├── YourModuleModule.cpp
    ├── Core/
    ├── Components/
    └── Tests/          # Unit tests
```

### 3. API Exposure Control

```cpp
// Public class - can be used by other modules
class YOURMODULE_API FPublicClass
{
    // ...
};

// Private class - internal use only
class FPrivateClass
{
    // ...
};
```

### 4. Module Loading Order

Control loading order in .uproject:

```json
{
  "Modules": [
    {
      "Name": "CoreModule",
      "Type": "Runtime",
      "LoadingPhase": "PostEngineInit"
    },
    {
      "Name": "GameplayModule",
      "Type": "Runtime",
      "LoadingPhase": "Default"
    }
  ]
}
```

### 5. Log Management

```cpp
// Declare in module header file
DECLARE_LOG_CATEGORY_EXTERN(LogYourModule, Log, All);

// Define in module implementation file
DEFINE_LOG_CATEGORY(LogYourModule);

// Usage
UE_LOG(LogYourModule, Warning, TEXT("Module message"));
```

### 6. Class Classification System

Based on the project structure, here's a recommended classification:

#### ManualCppOnly
**Purpose**: High-performance C++ API for other modules
**Features**:
- ✅ Other C++ modules can use
- ❌ Blueprint cannot inherit/call
- ⚡ High performance, no reflection system overhead

```cpp
// ManualCppOnly.h
#pragma once
#include "CoreMinimal.h"

/**
 * High-performance computation class
 * C++ modules only, Blueprint incompatible
 */
class MANUAL_API FManualCppOnly
{
public:
    /** High-performance data processing */
    static TArray<float> ProcessLargeDataset(const TArray<float>& Input);
    
    /** String hash calculation */
    static uint32 CalculateHash(const FString& Input);
    
    /** Mathematical calculation tools */
    static FVector CalculateTrajectory(const FVector& Start, const FVector& Velocity, float Time);
};
```

#### ManualExposed
**Purpose**: Blueprint-compatible game logic
**Features**:
- ✅ Other C++ modules can use
- ✅ Blueprint can inherit/call
- 🔄 Can internally call ManualCppOnly's high-performance functions

```cpp
// ManualExposed.h
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ManualExposed.generated.h"

/**
 * Blueprint-compatible game logic class
 * Supports both C++ and Blueprint usage
 */
UCLASS(BlueprintType, Blueprintable)
class MANUAL_API UManualExposed : public UObject
{
    GENERATED_BODY()

public:
    UManualExposed();

    /** Blueprint-callable data processing */
    UFUNCTION(BlueprintCallable, Category = "Manual")
    void ProcessGameData(const TArray<float>& GameData);
    
    /** Blueprint-callable trajectory calculation */
    UFUNCTION(BlueprintCallable, Category = "Manual")
    FVector CalculateProjectilePath(FVector StartPos, FVector Velocity, float TimeStep);
    
    /** Blueprint read-write property */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Manual")
    float ProcessingMultiplier;
    
    /** Blueprint read-only result */
    UPROPERTY(BlueprintReadOnly, Category = "Manual")
    TArray<float> ProcessedResults;

protected:
    /** Blueprint implementable event */
    UFUNCTION(BlueprintImplementableEvent, Category = "Manual")
    void OnProcessingComplete();
};
```

#### ManualInternal
**Purpose**: Internal module implementation details
**Features**:
- ❌ Other modules cannot use
- ❌ Blueprint cannot access
- 🔒 Encapsulates implementation details

```cpp
// ManualInternal.h (in Private folder)
#pragma once
#include "CoreMinimal.h"

/**
 * Internal module utility class
 * Not exposed externally, internal use only
 */
class FManualInternal
{
public:
    /** Internal cache management */
    static void InitializeCache();
    static void ClearCache();
    
    /** Internal configuration loading */
    static bool LoadModuleConfig();
    
    /** Internal logging tools */
    static void LogDebugInfo(const FString& Message);

private:
    static TMap<FString, float> InternalCache;
    static bool bIsInitialized;
};
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
1. Check dependencies in Build.cs
2. Confirm API macros are used correctly
3. Check include paths
4. Clean and rebuild

### Issue 3: Circular Dependencies

**Symptoms**: Module A depends on B, B also depends on A

**Solutions**:
1. Redesign module architecture
2. Extract common dependencies to a third module
3. Use forward declarations to reduce dependencies
4. Consider using interfaces for decoupling

### Issue 4: Module Loading Order Issues

**Symptoms**: Module loads at wrong time

**Solutions**:
1. Adjust LoadingPhase settings
2. Check module dependency relationships
3. Use appropriate loading phases

### Issue 5: Blueprint Integration Issues

**Symptoms**: C++ classes not visible in Blueprint

**Solutions**:
1. Ensure class inherits from UObject/AActor/UComponent
2. Add UCLASS macro with BlueprintType, Blueprintable
3. Use UFUNCTION for callable functions
4. Use UPROPERTY for accessible properties
5. Regenerate project files after changes

```cpp
// Correct Blueprint-compatible class
UCLASS(BlueprintType, Blueprintable)
class MANUAL_API UMyBlueprintClass : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "MyModule")
    void MyFunction();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MyModule")
    float MyProperty;
};
```

### Issue 6: Constructor Called Multiple Times

**Symptoms**: Constructor logs appear multiple times before game starts

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
UMyClass::UMyClass()
{
    // ✅ Good: Set default values
    MyProperty = 1.0f;
    bIsInitialized = false;
    
    // ❌ Bad: Don't do game logic here
    // StartGameplay();
    // LoadAssets();
}

void UMyClass::BeginPlay()
{
    Super::BeginPlay();
    // ✅ Good: Game logic goes here
    StartGameplay();
}
```

## Core Module Macros Explained

### DEFINE_LOG_CATEGORY(LogManual)
- **Purpose**: Creates a dedicated log category for the module
- **Usage**: `UE_LOG(LogManual, Warning, TEXT("Message"));`
- **Benefits**: Filter module-specific logs in editor

### LOCTEXT_NAMESPACE "FManualModule"
- **Purpose**: Sets namespace for localization text
- **Usage**: `LOCTEXT("Key", "Default Text")`
- **Benefits**: Supports game internationalization

### #undef LOCTEXT_NAMESPACE
- **Purpose**: Cleans up namespace definition
- **Importance**: Prevents affecting other files

### IMPLEMENT_MODULE(FManualModule, Manual)
- **Purpose**: Registers module with UE system
- **Format**: `IMPLEMENT_MODULE(ClassName, ModuleName)`
- **Critical**: Without this, module won't load!

## Conclusion

Unreal Engine's module system is a powerful tool for organizing large projects. Through proper module design, you can:

- Improve code maintainability
- Facilitate team collaboration
- Enable feature reuse
- Optimize compilation time

Remember, good module design is the foundation of successful UE projects. Start with small modules and gradually build your modular architecture.

## Example Project Structure

This handbook is based on the FirstModule project structure:

```
FirstModule/
├── Source/
│   ├── Auto/                    # IDE-created module
│   ├── Manual/                  # Manually created module
│   │   ├── Public/
│   │   │   ├── ManualModule.h
│   │   │   ├── ManualCppOnly.h     # C++ only classes
│   │   │   └── ManualExposed.h     # Blueprint compatible
│   │   └── Private/
│   │       ├── ManualModule.cpp
│   │       ├── ManualCppOnly.cpp
│   │       ├── ManualExposed.cpp
│   │       └── ManualInternal.cpp  # Internal implementation
│   └── Auto/                    # Example dependent module
└── Content/
    └── Manual/
        └── BP_ManualExposed     # Blueprint based on C++ class
```

This structure demonstrates the three-tier classification system for optimal code organization and Blueprint integration.
