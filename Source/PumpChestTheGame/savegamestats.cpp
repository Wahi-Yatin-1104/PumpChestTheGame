//Saransh Beniwal
#include "savegamestats.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include <chrono>

const FString USaveSystem::save_dir = FPaths::ProjectSavedDir() / TEXT("MySaves");
const FString USaveSystem::save_file = save_dir / TEXT("gains.txt");
const FString USaveSystem::backup_file = save_dir / TEXT("gains_backup.txt");
int32 USaveSystem::num_saves = 0;

struct save_timestamp{
    int32 year;
    int32 month;
    int32 day;
    int32 hour;
    int32 min;
    
    FString to_string() {
        return FString::Printf(TEXT("%d_%d_%d_%d_%d"), year, month, day, hour, min);
    }
};

bool USaveSystem::make_dir() {
    auto& pf = FPlatformFileManager::Get().GetPlatformFile();
    return pf.DirectoryExists(*save_dir) || pf.CreateDirectory(*save_dir);
}

bool USaveSystem::check_save(const FString& data) {
    if(data.IsEmpty()) return false;
    int32 commas = 0;
    for(auto c : data) {
        if(c == ',') commas++;
    }
    return commas >= 4;
}

void USaveSystem::backup_save() {
    if(FPaths::FileExists(save_file)) {
        FString data;
        if(FFileHelper::LoadFileToString(data, *save_file)) {
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            auto* tm = std::localtime(&time);
            
            save_timestamp ts;
            ts.year = tm->tm_year + 1900;
            ts.month = tm->tm_mon + 1;
            ts.day = tm->tm_mday;
            ts.hour = tm->tm_hour;
            ts.min = tm->tm_min;
            
            FString backup_name = backup_file + TEXT("_") + ts.to_string();
            FFileHelper::SaveStringToFile(data, *backup_name);
        }
    }
}

int32 USaveSystem::save_game(const UPlayer* p) {
    if(!p) {
        UE_LOG(LogTemp, Warning, TEXT("bruh where's the player???"));
        return SAVE_FAIL;
    }

    if(!make_dir()) {
        UE_LOG(LogTemp, Warning, TEXT("couldn't make save folder :("));
        return SAVE_FAIL;
    }
    
    //backup flies
    backup_save();
    
    FString save_data = p->get_stats().stats_to_string();
    
    if(FFileHelper::SaveStringToFile(save_data, *save_file)) {
        num_saves++;
        
        if(num_saves == 1) {
            UE_LOG(LogTemp, Warning, TEXT("First save! Don't forget to save often!"));
        }
        else if(num_saves == 10) {
            UE_LOG(LogTemp, Warning, TEXT("10 saves! You're getting strong!"));
        }
        else if(num_saves == 50) {
            UE_LOG(LogTemp, Warning, TEXT("50 saves! What a grinder!"));
        }
        else if(num_saves == 100) {
            UE_LOG(LogTemp, Warning, TEXT("100 SAVES! ABSOLUTE UNIT!"));
        }
        else if(num_saves % 25 == 0) {
            UE_LOG(LogTemp, Warning, TEXT("Save #%d! Keep it up!"), num_saves);
        }
        
        return SAVE_OK;
    }
    
    return SAVE_FAIL;
}

int32 USaveSystem::load_game(UPlayer* p) {
    if(!p) {
        UE_LOG(LogTemp, Warning, TEXT("no player to load to bruh"));
        return SAVE_FAIL;
    }

    if(!FPaths::FileExists(save_file)) {
        UE_LOG(LogTemp, Warning, TEXT("no saves found - time to get SWOLE"));
        return SAVE_FAIL;
    }
    
    FString save_data;
    if(FFileHelper::LoadFileToString(save_data, *save_file)) {
        if(!check_save(save_data)) {
            UE_LOG(LogTemp, Warning, TEXT("save!"));
            
            IFileManager& FM = IFileManager::Get();
            TArray<FString> backups;
            FString backup_pattern = backup_file + TEXT("_*");
            FM.FindFiles(backups, *backup_pattern);
            
            backups.Sort([](const FString& A, const FString& B) {
                return A > B;
            });
            
            if(backups.Num() > 0) {
                FString latest = save_dir / backups[0];
                if(FFileHelper::LoadFileToString(save_data, *latest)) {
                    if(!check_save(save_data)) {
                        UE_LOG(LogTemp, Warning, TEXT("backup also corrupted... RIP gains"));
                        return SAVE_CORRUPT;
                    }
                    UE_LOG(LogTemp, Warning, TEXT("loaded from backup!"));
                }
            } else {
                UE_LOG(LogTemp, Warning, TEXT("no backups found :("));
                return SAVE_FAIL;
            }
        }
        
        Stats loaded = Stats::from_string(save_data);
        p->set_stats(loaded);
        
        int32 level = loaded.level;
        if(level < 10) {
            UE_LOG(LogTemp, Warning, TEXT("Welcome back rookie!"));
        }
        else if(level < 25) {
            UE_LOG(LogTemp, Warning, TEXT("Back for more gains!"));
        }
        else if(level < 50) {
            UE_LOG(LogTemp, Warning, TEXT("The grind continues!"));
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("THE LEGEND RETURNS!"));
        }
        
        return SAVE_OK;
    }
    return SAVE_FAIL;
}

bool USaveSystem::quick_save(const UPlayer* p) {
    if(!p) return false;
    
    FString quick_file = save_dir / TEXT("quicksave.txt");
    return FFileHelper::SaveStringToFile(p->get_stats().stats_to_string(), *quick_file);
}
bool USaveSystem::quick_load(UPlayer* p) {
    if(!p) return false;
    
    FString quick_file = save_dir / TEXT("quicksave.txt");
    if(!FPaths::FileExists(quick_file)) {
        UE_LOG(LogTemp, Warning, TEXT("no quicksave found bro"));
        return false;
    }
    
    FString data;
    if(FFileHelper::LoadFileToString(data, *quick_file)) {
        if(check_save(data)) {
            p->set_stats(Stats::from_string(data));
            return true;
        }
        UE_LOG(LogTemp, Warning, TEXT("quicksave corrupted :("));
    }
    
    return false;
}

bool USaveSystem::save_backup(const UPlayer* p) {
    return p ? FFileHelper::SaveStringToFile(p->get_stats().stats_to_string(), *backup_file) : false;
}

bool USaveSystem::load_backup(UPlayer* p) {
    if(!p || !FPaths::FileExists(backup_file)) return false;
    
    FString data;
    if(FFileHelper::LoadFileToString(data, *backup_file)) {
        if(check_save(data)) {
            p->set_stats(Stats::from_string(data));
            return true;
        }
    }
    return false;
}
void USaveSystem::delete_saves() {
    auto& FM = IFileManager::Get();
    if(FPaths::DirectoryExists(save_dir)) {
        TArray<FString> files;
        FM.FindFiles(files, *save_dir, TEXT("*.txt"));
        
        for(auto& file : files) {
            FM.Delete(*(save_dir / file));
        }
        
        num_saves = 0;
        UE_LOG(LogTemp, Warning, TEXT("all progress deleted... time to start over"));
    }
}

bool USaveSystem::has_save() {
    return FPaths::FileExists(save_file) || FPaths::FileExists(backup_file);
}

void USaveSystem::print_debug() {
    UE_LOG(LogTemp, Warning, TEXT("DEBUG"));
    UE_LOG(LogTemp, Warning, TEXT("save folder: %s"), *save_dir);
    UE_LOG(LogTemp, Warning, TEXT("main save: %d"), FPaths::FileExists(save_file));
    UE_LOG(LogTemp, Warning, TEXT("backup: %d"), FPaths::FileExists(backup_file));
    UE_LOG(LogTemp, Warning, TEXT("times saved: %d"), num_saves);
    TArray<FString> backups;
    IFileManager::Get().FindFiles(backups, *(save_dir / TEXT("gains_backup_*.txt")), true, false);
    UE_LOG(LogTemp, Warning, TEXT("backup files: %d"), backups.Num());
}