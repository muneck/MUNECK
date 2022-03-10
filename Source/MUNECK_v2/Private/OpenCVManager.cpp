// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenCVManager.h"
<<<<<<< HEAD

// Sets default values
AOpenCVManager::AOpenCVManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    rootComp = CreateDefaultSubobject<USceneComponent>("Root");
    Screen_Raw = CreateDefaultSubobject<UStaticMeshComponent>("Screen Raw");
    Screen_Post = CreateDefaultSubobject<UStaticMeshComponent>("Screen Post");

    Brightness = 0;
    Multiply = 1;
    // Initialize OpenCV and webcam properties
    CameraID = 0;
    VideoTrackID = 0;
    isStreamOpen = false;
    VideoSize = FVector2D(1920, 1080);
    RefreshRate = 30.0f;

    
}

// Called when the game starts or when spawned
void AOpenCVManager::BeginPlay()
{
	Super::BeginPlay();

=======
#include <winbase.h>

#undef UpdateResource
// Sets default values
AOpenCVManager::AOpenCVManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    rootComp = CreateDefaultSubobject<USceneComponent>("Root");
    Screen_Raw = CreateDefaultSubobject<UStaticMeshComponent>("Screen Raw");
    Screen_Post = CreateDefaultSubobject<UStaticMeshComponent>("Screen Post");
}

// Called when the game starts or when spawned
void AOpenCVManager::BeginPlay(){
	Super::BeginPlay();

    //Brightness = 0;
    //Multiply = 1;
    //// Initialize OpenCV and webcam properties
    //CameraID = 0;
    //VideoTrackID = 0;
    //isStreamOpen = false;
    //VideoSize = FVector2D(1920, 1080);
    //RefreshRate = 30.0f;

    ////dll function get
    //dll_path = "D:\\UEproject\\MUNECK_v2\\Mediapipe_Face_Tracking.dll";//FIXME when distributing-we need relative path
    //FPaths::NormalizeDirectoryName(dll_path);
    //void* dllObj= FPlatformProcess::GetDllHandle(*dll_path);
    //Init_Graph = nullptr;
    //if (!dllObj)
    //{
    //    UE_LOG(LogTemp,Error, TEXT("Unable to load: %s"), *dll_path);
    //}
    //else
    //{
    //    Init_Graph = FPlatformProcess::GetDllExport(dllObj, TEXT("Mediapipe_Hand_Tracking_Init"));
    //    if (!Init_Graph)
    //    {
    //        UE_LOG(LogTemp, Error, TEXT("Export not found: Mediapipe_Hand_Tracking_Init"));
    //    }
    //    Track_face = FPlatformProcess::GetDllExport(dllObj, TEXT("Mediapipe_Hand_Tracking_Detect_Frame_Direct"));
    //    if (!Track_face)
    //    {
    //        UE_LOG(LogTemp, Error, TEXT("Export not found: Mediapipe_Hand_Tracking_Detect_Frame_Direct"));
    //    }
    //    Release_Graph = FPlatformProcess::GetDllExport(dllObj, TEXT("Mediapipe_Hand_Tracking_Release"));
    //    if (!Release_Graph)
    //    {
    //        UE_LOG(LogTemp, Error, TEXT("Export not found: Mediapipe_Hand_Tracking_Release"));
    //    }
    //}
    //Track_face = nullptr;
    //Release_Graph = nullptr;
    //if (dllLoader.IsFileExist(dll_path)) {
    //    std::cout << "dll存在" << std::endl;
    //    if (dllLoader.LoadDynamicModule(dll_path)) {
    //        std::cout << "dll加载成功！" << std::endl;

    //        // 获取Mediapipe_Hand_Tracking_Init
    //        void* p_Graph_Init = dllLoader.GetFunction("Mediapipe_Hand_Tracking_Init");
    //        if (p_Graph_Init != nullptr)
    //        {
    //            Init_Graph = (Func_InitGraph(p_Graph_Init));
    //            if (Init_Graph != nullptr)
    //            {
    //                std::cout << "Mediapipe_Hand_Tracking_Init获取成功" << std::endl;
    //            }

    //        }
    //        else
    //        {
    //            std::cout << "无法在dll中找到Mediapipe_Hand_Tracking_Init" << std::endl;
    //        }

    //        //获取Mediapipe_Hand_Tracking_Detect_Frame_Direct @@@@@@@@@@@@@@@@@@@@@@@@
    //        void* p_Mediapipe_Hand_Tracking_Detect_Frame_Direct = dllLoader.GetFunction("Mediapipe_Hand_Tracking_Detect_Frame_Direct");
    //        if (p_Mediapipe_Hand_Tracking_Detect_Frame_Direct != nullptr)
    //        {
    //            Track_face = (Func_Face_tracking)(p_Mediapipe_Hand_Tracking_Detect_Frame_Direct);
    //            if (Track_face != nullptr)
    //            {
    //                std::cout << "Mediapipe_Hand_Tracking_Detect_Frame_Direct获取成功" << std::endl;
    //            }
    //        }
    //        else
    //        {
    //            std::cout << "无法在dll中找到Mediapipe_Hand_Tracking_Detect_Frame_Direct" << std::endl;
    //        }

    //        //获取Mediapipe_Hand_Tracking_Release
    //        void* p_Mediapipe_Hand_Tracking_Release = dllLoader.GetFunction("Mediapipe_Hand_Tracking_Release");
    //        if (p_Mediapipe_Hand_Tracking_Release != nullptr)
    //        {
    //            Release_Graph = (Func_Release)(p_Mediapipe_Hand_Tracking_Release);
    //            if (Release_Graph != nullptr)
    //            {
    //                std::cout << "Mediapipe_Hand_Tracking_Release获取成功" << std::endl;
    //            }
    //        }
    //        else
    //        {
    //            std::cout << "无法在dll中找到Mediapipe_Hand_Tracking_Release" << std::endl;
    //        }

    //        //获取Mediapipe_Hand_Tracking_Release
    //        auto* p_Mediapipe_Hand_Tracking_Get = dllLoader.GetFunction("Get");
    //        if (p_Mediapipe_Hand_Tracking_Get != nullptr)
    //        {
    //            Get_Singleton = (Func_Get)(p_Mediapipe_Hand_Tracking_Get);
    //            if (Get_Singleton != nullptr)
    //            {
    //                std::cout << "Get获取成功" << std::endl;
    //            }
    //        }
    //        else
    //        {
    //            std::cout << "无法在dll中找到Get" << std::endl;
    //        }

    //    }
   /*     else {
            std::cout << "dll加载失败！" << std::endl;
        }
    }
    else {
        std::cout << "dll不存在" << std::endl;
    }*/

    //init model

    //mediapipe_hand_tracking_model_path = FString("D:\\UEproject\\MUNECK_v2\\face_mesh_desktop_live.pbtxt"); //FIXME-relative path

    //if (((Func_InitGraph)(Init_Graph))(TCHAR_TO_ANSI (*mediapipe_hand_tracking_model_path)))
    //{
    //    UE_LOG(LogTemp, Log, TEXT("Init_Graph Succ\n"));
    //}
    //else
    //{
    //    UE_LOG(LogTemp, Log, TEXT("Init_Graph Fail\n"));
    //    std::cout << "初始化模型失败\n";
    //}
    /* TEMP DISABLED camera component not needed
>>>>>>> 4cd8f15 (Final state)
    isStreamOpen = true;
    // Prepare the color data array
    ColorData.AddDefaulted(VideoSize.X * VideoSize.Y);
    // setup openCV
    cvSize = cv::Size(256, 256);//(VideoSize.X, VideoSize.Y);

    cvMat = cv::Mat(cvSize, CV_8UC4, ColorData.GetData());
    // create dynamic texture
    Camera_Texture2D = UTexture2D::CreateTransient(VideoSize.X, VideoSize.Y, PF_B8G8R8A8);

#if WITH_EDITORONLY_DATA
    Camera_Texture2D->MipGenSettings = TMGS_NoMipmaps;
#endif
    Camera_Texture2D->SRGB = Camera_RenderTarget->SRGB;
<<<<<<< HEAD
=======
    */
>>>>>>> 4cd8f15 (Final state)
}

// Called every frame
void AOpenCVManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
<<<<<<< HEAD
    RefreshTimer += DeltaTime;
    //FVector2D FacePos;
    if (isStreamOpen && RefreshTimer >= 1.0f / RefreshRate)
    {
        RefreshTimer -= 1.0f / RefreshRate;
        ReadFrame(FacePos); 
        OnNextVideoFrame();
    }
}

bool AOpenCVManager::ReadFrame(FVector2D fpos) {
=======
    // RefreshTimer += DeltaTime;
    //FVector2D FacePos;
    //ReadFrame(FacePos);
    /*TEMP DISABLED camera component not needed
    //if (isStreamOpen /*&& RefreshTimer >= 1.0f / RefreshRate*///)
    //{
    //    RefreshTimer -= 1.0f / RefreshRate;
    //    ReadFrame(FacePos); 
    //    OnNextVideoFrame();
    //}
    //*/
}

bool AOpenCVManager::ReadFrame(FVector2D fpos) {
    /*TEMP DISABLED camera component not needed
>>>>>>> 4cd8f15 (Final state)
    if (!Camera_Texture2D || !Camera_RenderTarget) return false;
    // Read the pixels from the RenderTarget and store them in a FColor array
    //TArray<FColor> SurfData;
    FRenderTarget* renderTarget = Camera_RenderTarget->GameThread_GetRenderTargetResource();

    renderTarget->ReadPixels(ColorData);
    int cvColorMode = CV_8UC4;
    // Get the color data
    cvMat = cv::Mat(cvSize, cvColorMode, ColorData.GetData());
<<<<<<< HEAD
    // do fun stuff here(convert things)
    DetectFace(cvMat, fpos);
=======

    //detect face
    unsigned char* pImageData = cvMat.data;
    */
    cv::Mat Cap;
    if (((Func_Face_tracking)Track_face)(gestureRecognitionResult,Cap)==1){
        UE_LOG(LogTemp, Log, TEXT("Detect results are : %f, %f, %f\n"), gestureRecognitionResult[0], gestureRecognitionResult[1], gestureRecognitionResult[2], gestureRecognitionResult[3], gestureRecognitionResult[4], gestureRecognitionResult[5]);
        std::cout << "识别结果为：" << gestureRecognitionResult[0] << " " << gestureRecognitionResult[1] << " " << gestureRecognitionResult[2] << std::endl;
        Turn = gestureRecognitionResult[0];
        Tilt = gestureRecognitionResult[1];
        Nod = gestureRecognitionResult[2];
        UE_LOG(LogTemp, Log, TEXT("Cap Type : %i \n"), Cap.type());
        // cv::imshow("ReturnCap", Cap);
    }
    else{
        UE_LOG(LogTemp, Log, TEXT("Track_face returns : %i \n"), ((Func_Face_tracking)Track_face)(gestureRecognitionResult, Cap));
        std::cout << "Mediapipe_Hand_Tracking_Detect_Frame_Direct执行失败！" << std::endl;
    }
    // do fun stuff here(convert things)
    //DetectFace(cvMat, fpos);
    
    /*TEMP DISABLED camera component not needed
>>>>>>> 4cd8f15 (Final state)
    //cvMat.convertTo(cvMat, -1, Multiply, Brightness);

    // show the openCV window
    if (!cvMat.empty())
        cv::imshow("Display", cvMat);
    
    void* TextureData = Camera_Texture2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);  //ask gong "lock"
    const int32 TextureDataSize = ColorData.Num() * 4;
    // set the texture data
    FMemory::Memcpy(TextureData, ColorData.GetData(), TextureDataSize);
    Camera_Texture2D->PlatformData->Mips[0].BulkData.Unlock();
    // Apply Texture changes to GPU memory
    Camera_Texture2D->UpdateResource();
<<<<<<< HEAD
    
    return true;
}

=======
    */
    
    
    return true;
}
/*
>>>>>>> 4cd8f15 (Final state)
bool AOpenCVManager::DetectFace(cv::Mat CVTexture, FVector2D& OutPos)
{
    cv::CascadeClassifier FaceCascade;
    FaceCascade.load("D:\\UEproject\\MUNECK_v2\\haarcascade_frontalface_default.xml");
    cv::Mat frame_gray;
    cv::cvtColor(CVTexture, frame_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frame_gray, frame_gray);
    //-- Detect faces
    std::vector<cv::Rect> faces;
    
    FaceCascade.detectMultiScale(frame_gray, faces);  //this line causes the error and the input figure is flawed (snow noise)
    
    for (int i = 0; i < faces.size(); i++)
    {
        cv::Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        ellipse(CVTexture, center, cv::Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, cv::Scalar(255, 0, 255), 4);

        cv::Mat faceROI = frame_gray(faces[i]);

    } 

    if (faces.size() > 0)
    {
        OutPos = FVector2D(faces[0].width / 2.f, faces[0].height / 2.f);
        return true;
    }
 
    return false;


}
<<<<<<< HEAD
=======
*/


void AOpenCVManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // Super::EndPlay(EndPlayReason);
    // if(((Func_Release)Release_Graph)()) UE_LOG(LogTemp, Log, TEXT("Release_Graph Succ\n"));
}
>>>>>>> 4cd8f15 (Final state)

