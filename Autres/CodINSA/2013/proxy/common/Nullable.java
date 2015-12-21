/*  1:   */ package common;
/*  2:   */ 
/*  3:   */ public class Nullable<T>
/*  4:   */   implements Accessors.Access<T>, Viewable<View>
/*  5:   */ {
/*  6: 7 */   public static final Nullable<?>.View NULL = new Nullable().view();
/*  7: 9 */   private T obj = null;
/*  8:   */   
/*  9:   */   public Nullable(T obj)
/* 10:   */   {
/* 11:12 */     set(obj);
/* 12:   */   }
/* 13:   */   
/* 14:   */   public Nullable() {}
/* 15:   */   
/* 16:   */   public boolean isNone()
/* 17:   */   {
/* 18:17 */     return this.obj == null;
/* 19:   */   }
/* 20:   */   
/* 21:   */   public boolean hasSome()
/* 22:   */   {
/* 23:18 */     return !isNone();
/* 24:   */   }
/* 25:   */   
/* 26:   */   public T get()
/* 27:   */   {
/* 28:22 */     if (this.obj == null) {
/* 29:23 */       throw new NullPointerException("Cannot get a null object from a Nullable.");
/* 30:   */     }
/* 31:24 */     return this.obj;
/* 32:   */   }
/* 33:   */   
/* 34:   */   public void set(T obj)
/* 35:   */   {
/* 36:29 */     if (obj == null) {
/* 37:30 */       throw new NullPointerException("Cannot give a null object to a Nullable. Use setNull() instead.");
/* 38:   */     }
/* 39:31 */     this.obj = obj;
/* 40:   */   }
/* 41:   */   
/* 42:   */   public void set(Nullable<? extends T> n)
/* 43:   */   {
/* 44:34 */     this.obj = n.obj;
/* 45:   */   }
/* 46:   */   
/* 47:   */   public void setNull()
/* 48:   */   {
/* 49:37 */     this.obj = null;
/* 50:   */   }
/* 51:   */   
/* 52:   */   public static <T> Nullable<T>.View NULL()
/* 53:   */   {
/* 54:42 */     return NULL;
/* 55:   */   }
/* 56:   */   
/* 57:   */   public class View
/* 58:   */     implements Viewable.ViewOf<Nullable<T>>
/* 59:   */   {
/* 60:   */     public View() {}
/* 61:   */     
/* 62:   */     public boolean isNone()
/* 63:   */     {
/* 64:45 */       return Nullable.this.isNone();
/* 65:   */     }
/* 66:   */     
/* 67:   */     public boolean hasSome()
/* 68:   */     {
/* 69:46 */       return Nullable.this.hasSome();
/* 70:   */     }
/* 71:   */     
/* 72:   */     public T get()
/* 73:   */     {
/* 74:47 */       return Nullable.this.get();
/* 75:   */     }
/* 76:   */   }
/* 77:   */   
/* 78:   */   public Nullable<T>.View view()
/* 79:   */   {
/* 80:52 */     return new View();
/* 81:   */   }
/* 82:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.Nullable
 * JD-Core Version:    0.7.0.1
 */