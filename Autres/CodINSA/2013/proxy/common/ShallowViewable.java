package common;

public abstract interface ShallowViewable<SV extends ShallowView>
{
  public abstract SV shallowView();
  
  public static abstract interface ShallowView {}
}


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.ShallowViewable
 * JD-Core Version:    0.7.0.1
 */