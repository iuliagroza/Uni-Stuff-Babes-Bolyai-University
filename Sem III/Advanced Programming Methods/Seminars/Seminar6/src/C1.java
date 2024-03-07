import java.util.ArrayList;

class A1 {}
class B1 extends A1 {}

class C1 extends B1 {}

class Amain1{
    A1  method1(ArrayList<? extends A1> list) {
        if(list.isEmpty())
            return null;
        else
            return list.get(1);
    }

    void method2(ArrayList<? super C1>  list, C1 elem) {
        list.add(elem);
    }

    void method3(C1 elem){
        ArrayList<A1> listA=new ArrayList<A1>();
        listA.add(new A1());

        ArrayList<B1> listB = new ArrayList<B1>();
        listB.add(new B1());

        ArrayList<C1> listC = new ArrayList<C1>();
        listC.add(new C1());

        this.method1(listA);
        this.method1(listB);
        this.method1(listC);
        this.method2(listA,elem);
        this.method2(listB,elem);
        this.method2(listC,elem);
    }
}