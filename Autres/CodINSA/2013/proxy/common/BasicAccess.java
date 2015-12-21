/*  1:   */ package common;
/*  2:   */ 
/*  3:   */ class BasicAccess<T>
/*  4:   */   implements Accessors.Access<T>
/*  5:   */ {
/*  6:   */   private T obj;
/*  7:   */   
/*  8:   */   public BasicAccess(T obj)
/*  9:   */   {
/* 10: 9 */     set(obj);
/* 11:   */   }
/* 12:   */   
/* 13:   */   public final T get()
/* 14:   */   {
/* 15:14 */     onGet();
/* 16:15 */     return this.obj;
/* 17:   */   }
/* 18:   */   
/* 19:   */   public final void set(T obj)
/* 20:   */   {
/* 21:20 */     if (obj == null) {
/* 22:21 */       throw new NullPointerException("BasicAccess does not allow null values.");
/* 23:   */     }
/* 24:22 */     if (canSet(obj))
/* 25:   */     {
/* 26:23 */       this.obj = obj;
/* 27:24 */       onSet();
/* 28:   */     }
/* 29:   */   }
/* 30:   */   
/* 31:   */   public void onGet() {}
/* 32:   */   
/* 33:   */   public void onSet() {}
/* 34:   */   
/* 35:   */   public boolean canSet(T obj)
/* 36:   */   {
/* 37:31 */     return true;
/* 38:   */   }
/* 39:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.BasicAccess
 * JD-Core Version:    0.7.0.1
 */