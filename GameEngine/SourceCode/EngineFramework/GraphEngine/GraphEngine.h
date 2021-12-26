//
// Created by MisThe on 2021/11/4.
// 图形渲染必须loop于主线程（可以使用wglMakeCurrent进行context线程切换但开销过高，且部分API必须在主线程使用）
//

#ifndef GAMEENGINE_GRAPHENGINE_H
#define GAMEENGINE_GRAPHENGINE_H


#include "Function/Shader.h"
#include "../EngineSetting.h"
#include "../../Components/GameObject.h"
#include "Controller/BasePipeline.h"
#include "Controller/MeshController.h"

class GraphEngine
{
public:
    static std::queue<GLFWwindow*> staticWindowQueue;
private:
    Float2 screenResolution;
    static GraphEngine* engine;
    class EngineWindow
    {
    public:
        EngineWindow(GLFWwindow*window,int windowId):window(window){this->windowId = windowId;}
        ~EngineWindow()
        {
            glfwMakeContextCurrent(this->window);
            CommonUtils::SafeCall(this->func);
            glfwDestroyWindow(this->window);
            this->window = nullptr;
        }
        void setDestroyCallBack(std::function<void()> func)
        {
            this->func = func;
        }
        void useWindow()
        {
            glfwMakeContextCurrent(this->window);
        }
        bool render()
        {
            //待优化
            if (glfwWindowShouldClose(this->window)) {
                return false;
            }
            glfwMakeContextCurrent(this->window);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
            BasePipeline::Render(this->windowId);
            glfwSwapBuffers(this->window);
            return true;
        }
        int getId()
        {
            return this->windowId;
        }
        GLFWwindow* window;
    private:
        int windowId;
//        GLFWwindow* window;
        std::function<void()> func;
    };
    std::queue<EngineWindow*> windowQueue;
    int windowNum = -1;     //为了管理shader需要创建一次不保留的window
public:
    ~GraphEngine()
    {
        CommonUtils::TraverQueue<EngineWindow*>(this->windowQueue,[](EngineWindow* ew)
        {
            delete ew;
        });
    }
    static GraphEngine* GetEngine()
    {
        engine = (engine == nullptr)?(new GraphEngine()):engine;
        return engine;
    }
    static int AddWindow(int setIndex)
    {
        return GetEngine()->addWindow(setIndex);
    }
    static void UpdateWindowQueue()
    {
        CommonUtils::TraverQueueBool<GLFWwindow*>(&staticWindowQueue,[](GLFWwindow* window)->bool{
            if (window == nullptr)
            {
                return false;
            }
            return true;
        });
    }
    static void Run()
    {
        GetEngine()->runWindows();
    }
    static void Pause()
    {

    }
    static void Stop()
    {

    }
    static void DeleteWindow(int windowIndex)
    {
        GetEngine()->deleteWindow(windowIndex);
    }
    static void SetVSync(bool flag)
    {
        //受硬件和驱动影响不一定有效
        glfwSwapInterval(flag);
    }
private:
    GraphEngine()
    {
        initEvent();
        init();
    }

    void initEvent()
    {
        EventCenter::AddEvent("UseWindow",[this](int index){ this->useWindow(index);});
        EventCenter::AddEvent("AddWindow",[](long index){ *(int*)index = GraphEngine::AddWindow(index);});
        EventCenter::AddEvent("DeleteWindow",[](int index){GraphEngine::DeleteWindow(index);});
    }
    void init()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        //获取屏幕参数
        int monitorCount;
        GLFWmonitor** monitor = glfwGetMonitors(&monitorCount);
        const GLFWvidmode* videoMode = glfwGetVideoMode(monitor[0]);
        this->screenResolution = Float2(videoMode->width,videoMode->height);
    }
    void useWindow(int index)
    {
        CommonUtils::TraverQueue<EngineWindow*>(this->windowQueue,[&index](EngineWindow*ew){
            if (ew->getId() == index)
            {
                ew->useWindow();
            }
        });
    }
    int addWindow(int setIndex)
    {
        GLFWwindow* window = glfwCreateWindow(EngineSetting::GetScreenWidth(setIndex) * this->screenResolution.x, EngineSetting::GetScreenHeight(setIndex) * this->screenResolution.y, "LearnOpenGL", nullptr, nullptr);
        if (window == nullptr)
        {
            glfwTerminate();
            GameLog::LogError("Engine Init","init window failed");
        }
        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            GameLog::LogError("Engine Init","init glad failed");
        }
        Color backColor = EngineSetting::GetBackColor(setIndex);
        glClearColor(backColor.r,backColor.g,backColor.b,backColor.a);
        this->windowNum++;
        ShaderController::CompileShader(this->windowNum);
        MeshController::InitMesh(this->windowNum);
        windowQueue.push(new EngineWindow(window,this->windowNum));
        staticWindowQueue.push(window);
        return windowNum;
    }
    void runWindows()
    {
        //执行后主线程被完全占用
        std::function<bool(EngineWindow*)> func = [](EngineWindow*ew){ if (ew->render()){return true;}delete ew; return false;};
        while (this->windowQueue.size() > 0)
        {
            CommonUtils::TraverQueueBool<EngineWindow*>(&this->windowQueue,func);
            glfwPollEvents();
//            std::cout << Time::CalculateFrame() << std::endl;
        }
        glfwTerminate();
    }
    void deleteWindow(int id)
    {
        std::function<bool(EngineWindow*)> func = [&id](EngineWindow*ew){ if (ew->getId() == id){delete ew;return false;}return true;};
        CommonUtils::TraverQueueBool<EngineWindow*>(&this->windowQueue,func);
    }
};


#endif

//GAMEENGINE_GRAPHENGINE_H
