/*  1:   */ package command;
/*  2:   */ 
/*  3:   */ import common.Util;
/*  4:   */ import model.Plane.Type;
/*  5:   */ 
/*  6:   */ public class BuildPlaneCommand
/*  7:   */   extends Command
/*  8:   */ {
/*  9:   */   public final Plane.Type requestedType;
/* 10:   */   
/* 11:   */   public BuildPlaneCommand(Plane.Type requestedType)
/* 12:   */   {
/* 13:12 */     Util.checkNull(requestedType);
/* 14:13 */     this.requestedType = requestedType;
/* 15:   */   }
/* 16:   */   
/* 17:   */   public String toString()
/* 18:   */   {
/* 19:18 */     return "build " + (this.requestedType == Plane.Type.MILITARY ? "military" : "commercial");
/* 20:   */   }
/* 21:   */   
/* 22:   */   public void match()
/* 23:   */     throws BuildPlaneCommand
/* 24:   */   {
/* 25:22 */     throw this;
/* 26:   */   }
/* 27:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     command.BuildPlaneCommand
 * JD-Core Version:    0.7.0.1
 */