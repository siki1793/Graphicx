class view{
    public:
        void drawPoint(int,int);
        void drawLine(POINT,POINT);
        void drawCurve(POINT,POINT,float);
        void drawAxis(void);
        void relocate(void);
        void bezier(void);
        void lagrange(void);
        static void renderFunction();
        static void reshape (int, int);
};
