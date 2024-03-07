class A {
    protected int f1;
    static int s1=0;
    public A(int a)  {
        this.f1=a*s1;
        s1=s1+1;
    }
    static int getS()  {
        return getS1(s1);
    }
    int getS1(int x)  {
        return (x*getS());
    }
}