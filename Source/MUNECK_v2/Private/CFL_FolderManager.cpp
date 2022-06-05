// Fill out your copyright notice in the Description page of Project Settings.


#include "CFL_FolderManager.h"


TArray<FString> UCFL_FolderManager::FindFilesRecursive(FString Path, FString Filter, bool InFiles, bool InDirectory)
{
    TArray<FString> FilePathList;
    //�������  
    FilePathList.Empty();
    //�����ļ������������FileList  
    IFileManager::Get().FindFilesRecursive(FilePathList, *Path, *Filter, InFiles, InDirectory);
    //���ؽ��  
    return FilePathList;
}