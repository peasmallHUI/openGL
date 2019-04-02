# OpenGL 编程指南

## 第一章 OpenGL 概述
1. 什么是OpenGL
    >是一种API，一种图形库

2. 初识OpenGL程序
    - 主要操作步骤：  
        - 设置数据  
        - 各种着色器判断位置等属性  
        - 光栅化  
        - 片元着色器计算颜色
        - 各种测试

3. OpenGL语法

4. OpenGL渲染管线
    - 顶点数据：VBO,VAO……
    - 顶点着色器：处理顶点位置坐标等
    - 其他着色器：细分着色器，几何着色器……
    - 光栅化过程：剪切，片元
    - 片元着色器：计算颜色，光照……
    - 测试于混合：深度测试，模板测试，混合……

5. 第一个程序
    >初始化GULT/GLFW等第三方库  
    >OpenGL初始化：Gen, Bind, Data， 顶点、片元着色器……  
    >OpenGL渲染


## 第二章 着色器基础

1. 着色器与OpenGL

2. OpenGL的可编程管线
    >顶点着色、细分着色、几何着色、片元着色

3. OpenGL着色语言概述
    ```glsl
    #version 430 core
    layout ( location = 0) in vec3 aPos;
    out vec4 Position;
    uniform mat4 Model;

    void main()
    {
        //……………………
    }
    
    ```

4. 数据块接口
    ```glsl
    //uniform块
    uniform Matrices
    {
        mat4 ModelView;
        mat4 Projection;
        mat4 Color;
    };  // 访问块成员时使用ModelView,Projection
    ```
    >`glGetUniformBlockIndex()`, `glBindBufferRange()`

5. 着色器的编译
    ```glsl
    GLuint glCreateShader(GLenum type);
    void glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
    void glCompileShader(GLuint shader);
    void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, char* infoLog);
    GLuint glCreateProgram(void);
    void glAttachShader(GLuint program, GLuint shader);
    void glLinkProgram(GLuint program);
    void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, char* infoLog);
    void glUseProgram(GLuint program);
    ```

6. 着色器子程序
    >静态可用`if`语句选择执行  
    >着色器子程序类似于函数指针，可以实现动态子程序选择过程
    ```glsl
    //声明一个着色器子程序
    subroutine vec4 LightFunc(vec3);                //1st_step

    subroutine (LightFunc) vec4 ambient(vec3 n)     //2nd_step
    {
        //do something...
    }

    subroutine (LightFunc) vec4 diffuse(vec3 n)     //2nd_step
    {
        //do something...
    }

    subroutine uniform LightFunc materialShader;    //3rd_step
    ```

    ```glsl
    //调用一个着色器子程序
    GLint materialShaderLoc;
    GLuint ambientIndex;
    GLuint diffuseIndex;

    glUseProgram(program);

    materialShaderLoc = glGetSubroutineUniformLocation(program, GL_VERTEX_SHADER, "materialShader");

    if (materialShaderLoc < 0)
    {
        //error
    }

    ambientIndex = glGetSubroutineIndex(program, GL_VERTEX_SHADER, "ambient");
    diffuseIndex = glGetSubroutineIndex(program, GL_VERTEX_SHADER, "diffuse");

    if(ambientIndex == GL_INVALID_INDEX || diffuseIndex == INVALID_INDEX)
    {
        //error
    }
    else
    {
        GLsizei n;
        glGetIntegerv(GL_MAX_SUBROUTINE_UNIFORM_LOCATION, &n);
        GLuint* indices = new GLint[n];
        indices[materialShaderLoc] = ambientIndex;

        glUniformSubroutinesuiv(GL_VERTEX_SHADER, n, indices);

        delete [] indices;
    }
    ```

7. 独立的着色器对象


## 第三章 OpenGL绘制方式

1. OpenGL图元
    - 点：默认一个像素大小
    - 线：条带，循环线
    - 三角形：条带，扇面
    - 多边形正面顶点**逆时针**排列，背面可裁剪（GL_CCW）

2. OpenGL缓存数据
    - 创建与分配
        ```glsl
        void glGenBuffers(GLsizei n, GLuint* buffers);
        void glBindBuffer(GLenum target, GLuint buffer);
        ```

    - 向缓存输入输出数据
        ```glsl
        void glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
        void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);  //部分初始化
        void glCopyBufferSubData(GLenum readtarget, GLenum wrtietarget, GLintptr readoffset, GLintptr writeoffset, GLsizeiptr size);//互相拷贝
        void glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid* data);  //回读数据
        ```

    - 访问缓存的内容
        ```glsl
        //返回指针，映射缓存区域
        void* glMapBuffer(GLenum target, GLenum access);
        void* glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
        GLboolean glUnmapBuffer(GLenum target);
        ```
    
3. 顶点规范

4. OpenGL的绘制命令

5. 多实例渲染

## 第四章 颜色、像素和帧缓存

1. 基本颜色理论 
    > RGBA、像素深度（bit depth）

2. 缓存及其作用
    > 颜色缓存、深度缓存、模板缓存
    - 清除缓存
        ```glsl
        //设置清除值
        void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
        void glClearDepth(GLclampd depth);
        void glClearStencil(GLint s);
        
        //清除
        void glClear(GLbitfield mask);
        ```
    
    - 缓存的掩码
        ```glsl
        void glColorMask(GLboolean red, GLboolean green, GLboolean blue);
        void glDepthMask(GLboolean flag);
        void glStencilMask(GLboolean mask);
        ```

3. 颜色与OpenGL
    - 片元着色器直接生成颜色；顶点附加颜色数据；片元着色器计算生成；外部纹理数据  
    - 归一化数据、顶点颜色（`glVertexAttribPointer`、`layout (location = 1)`）  
    - 光栅化：顶点着色阶段与片元着色阶段之间，插值等操作

4. 多重采样
    >MSAA(MultiSamplingAntiAliasing)：每个像素多次采样

5. 片元的测试与操作
    
