/* 1:  */ package model;
/* 2:  */ 
/* 3:  */ public class OutOfSyncException
/* 4:  */   extends RuntimeException
/* 5:  */ {
/* 6:  */   public OutOfSyncException(String msg)
/* 7:  */   {
/* 8:8 */     super("You tried to access out of sync data: " + msg);
/* 9:  */   }
/* ::  */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     model.OutOfSyncException
 * JD-Core Version:    0.7.0.1
 */