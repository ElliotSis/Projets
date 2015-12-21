/*  1:   */ package command;
/*  2:   */ 
/*  3:   */ import common.Util;
/*  4:   */ import model.Country.Request.View;
/*  5:   */ 
/*  6:   */ public class CancelRequestCommand
/*  7:   */   extends Command
/*  8:   */ {
/*  9:   */   public final Country.Request.View request;
/* 10:   */   
/* 11:   */   private CancelRequestCommand(Country.Request.View r)
/* 12:   */   {
/* 13:15 */     Util.checkNull(r);
/* 14:16 */     this.request = r;
/* 15:   */   }
/* 16:   */   
/* 17:   */   public String toString()
/* 18:   */   {
/* 19:21 */     return "cancel request " + this.request.rqId();
/* 20:   */   }
/* 21:   */   
/* 22:   */   public void match()
/* 23:   */     throws CancelRequestCommand
/* 24:   */   {
/* 25:25 */     throw this;
/* 26:   */   }
/* 27:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     command.CancelRequestCommand
 * JD-Core Version:    0.7.0.1
 */