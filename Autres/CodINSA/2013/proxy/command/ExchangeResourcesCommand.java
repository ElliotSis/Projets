/*  1:   */ package command;
/*  2:   */ 
/*  3:   */ import common.Util;
/*  4:   */ import model.Plane.FullView;
/*  5:   */ 
/*  6:   */ public class ExchangeResourcesCommand
/*  7:   */   extends Command
/*  8:   */ {
/*  9:   */   public final Plane.FullView planeSrc;
/* 10:   */   public final double militarQuantity;
/* 11:   */   public final double fuelQuantity;
/* 12:   */   public final boolean deleteResources;
/* 13:   */   
/* 14:   */   public ExchangeResourcesCommand(Plane.FullView p, double mq, double fq, boolean delete)
/* 15:   */   {
/* 16:19 */     Util.checkNull(p);
/* 17:20 */     this.planeSrc = p;
/* 18:21 */     this.militarQuantity = mq;
/* 19:22 */     this.fuelQuantity = fq;
/* 20:23 */     this.deleteResources = delete;
/* 21:   */   }
/* 22:   */   
/* 23:   */   public String toString()
/* 24:   */   {
/* 25:28 */     return "loadResource " + this.planeSrc.id() + " : militar => " + this.militarQuantity + "; fuel => " + this.fuelQuantity;
/* 26:   */   }
/* 27:   */   
/* 28:   */   public void match()
/* 29:   */     throws ExchangeResourcesCommand
/* 30:   */   {
/* 31:33 */     throw this;
/* 32:   */   }
/* 33:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     command.ExchangeResourcesCommand
 * JD-Core Version:    0.7.0.1
 */