// Fill out your copyright notice in the Description page of Project Settings.


#include "CFL_FolderManager.h"


TArray<FString> UCFL_FolderManager::FindFilesRecursive(FString Path, FString Filter, bool InFiles, bool InDirectory)
{
    TArray<FString> FilePathList;
    //清空数组  
    FilePathList.Empty();
    //查找文件并将结果赋给FileList  
    IFileManager::Get().FindFilesRecursive(FilePathList, *Path, *Filter, InFiles, InDirectory);
    //返回结果  
    return FilePathList;
}