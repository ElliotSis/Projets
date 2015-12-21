/*  1:   */ package common;
/*  2:   */ 
/*  3:   */ public class Accessors
/*  4:   */ {
/*  5:   */   public static abstract interface Access<T>
/*  6:   */     extends Accessors.RAccess<T>, Accessors.WAccess<T>
/*  7:   */   {}
/*  8:   */   
/*  9:   */   static class AccessFailureException
/* 10:   */     extends Exception
/* 11:   */   {
/* 12:   */     private static final long serialVersionUID = 1L;
/* 13:   */     
/* 14:   */     public AccessFailureException() {}
/* 15:   */     
/* 16:   */     public AccessFailureException(String msg)
/* 17:   */     {
/* 18:33 */       super();
/* 19:   */     }
/* 20:   */     
/* 21:   */     public AccessFailureException(Exception cause)
/* 22:   */     {
/* 23:34 */       super();
/* 24:   */     }
/* 25:   */   }
/* 26:   */   
/* 27:   */   public static abstract interface FAccess<T>
/* 28:   */     extends Accessors.FRAccess<T>, Accessors.FWAccess<T>
/* 29:   */   {}
/* 30:   */   
/* 31:   */   public static abstract interface FRAccess<T>
/* 32:   */   {
/* 33:   */     public abstract T get()
/* 34:   */       throws Accessors.FRAccess.Failure;
/* 35:   */     
/* 36:   */     public static class Failure
/* 37:   */       extends Accessors.AccessFailureException
/* 38:   */     {
/* 39:   */       private static final long serialVersionUID = 1L;
/* 40:   */       
/* 41:   */       public Failure() {}
/* 42:   */       
/* 43:   */       public Failure(String msg)
/* 44:   */       {
/* 45:41 */         super();
/* 46:   */       }
/* 47:   */       
/* 48:   */       public Failure(Exception cause)
/* 49:   */       {
/* 50:42 */         super();
/* 51:   */       }
/* 52:   */     }
/* 53:   */   }
/* 54:   */   
/* 55:   */   public static abstract interface FWAccess<T>
/* 56:   */   {
/* 57:   */     public abstract void set(T paramT)
/* 58:   */       throws Accessors.FWAccess.Failure;
/* 59:   */     
/* 60:   */     public static class Failure
/* 61:   */       extends Accessors.AccessFailureException
/* 62:   */     {
/* 63:   */       private static final long serialVersionUID = 1L;
/* 64:   */       
/* 65:   */       public Failure() {}
/* 66:   */       
/* 67:   */       public Failure(String msg)
/* 68:   */       {
/* 69:51 */         super();
/* 70:   */       }
/* 71:   */       
/* 72:   */       public Failure(Exception cause)
/* 73:   */       {
/* 74:52 */         super();
/* 75:   */       }
/* 76:   */     }
/* 77:   */   }
/* 78:   */   
/* 79:   */   public static abstract interface RAccess<T>
/* 80:   */   {
/* 81:   */     public abstract T get();
/* 82:   */   }
/* 83:   */   
/* 84:   */   public static abstract interface WAccess<T>
/* 85:   */   {
/* 86:   */     public abstract void set(T paramT);
/* 87:   */   }
/* 88:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.Accessors
 * JD-Core Version:    0.7.0.1
 */