package common;

public abstract interface Viewable<V extends View>
{
  public abstract V view();
  
  public static abstract interface View {}
  
  public static abstract interface ViewOf<T>
    extends Viewable.View
  {}
}


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.Viewable
 * JD-Core Version:    0.7.0.1
 */