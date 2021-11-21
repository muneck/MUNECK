// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenCVManager.h"

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
}

// Called every frame
void AOpenCVManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
    if (!Camera_Texture2D || !Camera_RenderTarget) return false;
    // Read the pixels from the RenderTarget and store them in a FColor array
    //TArray<FColor> SurfData;
    FRenderTarget* renderTarget = Camera_RenderTarget->GameThread_GetRenderTargetResource();

    renderTarget->ReadPixels(ColorData);
    int cvColorMode = CV_8UC4;
    // Get the color data
    cvMat = cv::Mat(cvSize, cvColorMode, ColorData.GetData());
    // do fun stuff here(convert things)
    DetectFace(cvMat, fpos);
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
    
    return true;
}

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

