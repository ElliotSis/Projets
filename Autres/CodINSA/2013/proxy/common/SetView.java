/*  1:   */ package common;
/*  2:   */ 
/*  3:   */ import java.util.Set;
/*  4:   */ 
/*  5:   */ public abstract interface SetView<T>
/*  6:   */   extends CollectionView<T>
/*  7:   */ {
/*  8:   */   public abstract Set<T> asUnmodifiableSet();
/*  9:   */   
/* 10:   */   public static class ShallowOf<T>
/* 11:   */     extends CollectionView.ShallowOf<T>
/* 12:   */     implements SetView<T>
/* 13:   */   {
/* 14:   */     public ShallowOf(Set<T> src)
/* 15:   */     {
/* 16:17 */       super();
/* 17:   */     }
/* 18:   */     
/* 19:   */     public Set<T> asUnmodifiableSet()
/* 20:   */     {
/* 21:22 */       return (Set)delegate();
/* 22:   */     }
/* 23:   */   }
/* 24:   */   
/* 25:   */   public static class Transform<U>
/* 26:   */     extends CollectionView.Transform<U>
/* 27:   */     implements SetView<U>, Set<U>, CollectionWrapper
/* 28:   */   {
/* 29:   */     public <T> Transform(Set<T> src, Util.Converter<T, U> transformer)
/* 30:   */     {
/* 31:31 */       super(transformer);
/* 32:   */     }
/* 33:   */     
/* 34:   */     public Set<U> asUnmodifiableSet()
/* 35:   */     {
/* 36:34 */       return this;
/* 37:   */     }
/* 38:   */   }
/* 39:   */   
/* 40:   */   public static class Of<V extends Viewable.View>
/* 41:   */     extends SetView.Transform<V>
/* 42:   */     implements SetView<V>
/* 43:   */   {
/* 44:   */     public <T extends Viewable<V>> Of(Set<T> src)
/* 45:   */     {
/* 46:53 */       super(Util.getViewer());
/* 47:   */     }
/* 48:   */   }
/* 49:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.SetView
 * JD-Core Version:    0.7.0.1
 */