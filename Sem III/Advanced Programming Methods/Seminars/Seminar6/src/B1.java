import java.util.ArrayList;

class A {}
class B extends A {}

class C extends A {}

class Amain {
    A  method1(ArrayList<? extends A> list) {
        if (list.isEmpty())
            return null;
        else
            return list.get(1);
    }

    void method2(ArrayList<? extends A>  list) {
        list.add(null);
    }

    void method3() {
        ArrayList<A> listA = new ArrayList<A>();
        listA.add(new A());

        ArrayList<B> listB = new ArrayList<B>();
        listB.add(new B());

        ArrayList<C> listC = new ArrayList<C>();
        listC.add(new C());

        this.method1(listA);
        this.method1(listB);
        this.method1(listC);
        this.method2(listA);
        this.method2(listB);
        this.method2(listC);
    }
}