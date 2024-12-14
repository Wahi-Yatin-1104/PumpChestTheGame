//Saransh Beniwal
#pragma once
#include "gameplayer.h"
#include "CoreMinimal.h"
#include "savesys.generated.h"

UCLASS()
class USaveSystem : public UObject {
    GENERATED_BODY()

private:
    static const FString save_dir;
    static const FString save_file;
    static const FString backup_file;
    
    static bool make_dir();
    static bool check_save(const FString& data);
    static void backup_save();
    
    static int32 num_saves;
    
    static const int32 SAVE_OK = 0;
    static const int32 SAVE_FAIL = 1;
    static const int32 SAVE_CORRUPT = 2;

public:
    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    static int32 save_game(const UPlayer* p);

    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    static int32 load_game(UPlayer* p);

    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    static bool quick_save(const UPlayer* p);
    
    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    static bool quick_load(UPlayer* p);
    
    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    static bool save_backup(const UPlayer* p);
    
    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    static bool load_backup(UPlayer* p);
    
    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    static void delete_saves();
    
    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    static bool has_save();
    
    UFUNCTION(BlueprintCallable, Category = "SaveSystem")
    static void print_debug();
};