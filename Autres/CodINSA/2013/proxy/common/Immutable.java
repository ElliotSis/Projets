/*  1:   */ package common;
/*  2:   */ 
/*  3:   */ public class Immutable<V extends Viewable.View>
/*  4:   */   implements Viewable<V>, Copyable, ShallowCopyable
/*  5:   */ {
/*  6:   */   public final V view;
/*  7:   */   
/*  8:   */   public <T extends Viewable<V>> Immutable(Unique<T> uniqueObject)
/*  9:   */   {
/* 10:24 */     this.view = ((Viewable)uniqueObject.take()).view();
/* 11:   */   }
/* 12:   */   
/* 13:   */   public <T> Immutable(Unique<T> uniqueObject, Util.Converter<T, V> viewer)
/* 14:   */   {
/* 15:28 */     this.view = ((Viewable.View)viewer.convert(uniqueObject.take()));
/* 16:   */   }
/* 17:   */   
/* 18:   */   public V view()
/* 19:   */   {
/* 20:44 */     return this.view;
/* 21:   */   }
/* 22:   */   
/* 23:   */   public Immutable<V> copy(Copyable.Context context)
/* 24:   */   {
/* 25:49 */     return this;
/* 26:   */   }
/* 27:   */   
/* 28:   */   public Immutable<V> shallowCopy()
/* 29:   */   {
/* 30:54 */     return this;
/* 31:   */   }
/* 32:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.Immutable
 * JD-Core Version:    0.7.0.1
 */