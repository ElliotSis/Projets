/*  1:   */ package common;
/*  2:   */ 
/*  3:   */ import java.util.IdentityHashMap;
/*  4:   */ 
/*  5:   */ public abstract interface Copyable
/*  6:   */ {
/*  7:   */   public abstract Object copy(Context paramContext);
/*  8:   */   
/*  9:   */   public static class Context
/* 10:   */     extends IdentityHashMap<Object, Object>
/* 11:   */   {
/* 12:   */     @Deprecated
/* 13:   */     public Object put(Object key, Object value)
/* 14:   */     {
/* 15:35 */       if (!key.getClass().isInstance(key)) {
/* 16:36 */         throw new Error("Value must be an instance of the key's class.");
/* 17:   */       }
/* 18:37 */       return super.put(key, value);
/* 19:   */     }
/* 20:   */     
/* 21:   */     @Deprecated
/* 22:   */     public Object get(Object key)
/* 23:   */     {
/* 24:42 */       return super.get(key);
/* 25:   */     }
/* 26:   */     
/* 27:   */     public <K, V extends K> void putSafe(K key, V value)
/* 28:   */     {
/* 29:45 */       super.put(key, value);
/* 30:   */     }
/* 31:   */     
/* 32:   */     public <K> K getSafe(K t)
/* 33:   */     {
/* 34:49 */       return super.get(t);
/* 35:   */     }
/* 36:   */   }
/* 37:   */   
/* 38:   */   public static abstract interface Copier<T>
/* 39:   */   {
/* 40:   */     public abstract T copy(T paramT, Copyable.Context paramContext);
/* 41:   */   }
/* 42:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.Copyable
 * JD-Core Version:    0.7.0.1
 */