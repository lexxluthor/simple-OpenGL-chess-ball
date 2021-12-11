/* lexxaedr 02.05.2020 */

namespace kagl
{
    class anim;
    class object
    {
    public:
        virtual void Draw(anim* Anim) {}
        virtual void Keyboard(anim* Ani, int key) {}
    };
    class anim
    {
    private:
        static const int MaxNumOfObjects = 1000;
        int NumOfObjects;
        object* Objects[MaxNumOfObjects];
        anim();
        static anim Instance;
        long StartTime, OldTime, PauseTime;
        int IsPause;
    public:
        double SyncTime, DeltaTime;
        ~anim();
        void Clear();
        static anim& Get();
        anim& operator<<(object* Obj);
        static void Display();
        static void Keyboard( unsigned char key, int x, int y );
        static void Reshape(int w, int h);
        void Run();
        void Timer();
    };
    class cube : public object
    {
    private:
        double angle;
        double speed;
        double size;
    public:
        explicit cube(double s);
        void Draw(anim* ani);
        void Keyboard(anim* ani, int key);
    };
}