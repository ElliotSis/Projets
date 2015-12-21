/*  1:   */ package common;
/*  2:   */ 
/*  3:   */ public abstract interface Function<A, R>
/*  4:   */ {
/*  5:   */   public abstract R apply(A paramA);
/*  6:   */   
/*  7:   */   public static abstract class Void<A>
/*  8:   */     implements Function<A, Void>
/*  9:   */   {
/* 10:   */     public final Void apply(A arg)
/* 11:   */     {
/* 12: 9 */       exec(arg);
/* 13:10 */       return null;
/* 14:   */     }
/* 15:   */     
/* 16:   */     public abstract void exec(A paramA);
/* 17:   */   }
/* 18:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.Function
 * JD-Core Version:    0.7.0.1
 */