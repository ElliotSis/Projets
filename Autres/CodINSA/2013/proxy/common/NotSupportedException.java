/*  1:   */ package common;
/*  2:   */ 
/*  3:   */ public class NotSupportedException
/*  4:   */   extends RuntimeException
/*  5:   */ {
/*  6:   */   private static final long serialVersionUID = 1L;
/*  7:   */   
/*  8:   */   public NotSupportedException() {}
/*  9:   */   
/* 10:   */   public NotSupportedException(String msg)
/* 11:   */   {
/* 12:11 */     super(msg);
/* 13:   */   }
/* 14:   */   
/* 15:   */   public static NotSupportedException notImplementedYet()
/* 16:   */   {
/* 17:15 */     return new NotSupportedException("Not implemented yet!");
/* 18:   */   }
/* 19:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.NotSupportedException
 * JD-Core Version:    0.7.0.1
 */