/*  1:   */ package model;
/*  2:   */ 
/*  3:   */ import common.Copyable.Context;
/*  4:   */ import common.Unique;
/*  5:   */ 
/*  6:   */ public class MovingEntity
/*  7:   */   extends MaterialEntity
/*  8:   */ {
/*  9:   */   public final Coord position;
/* 10:   */   public final Coord inertia;
/* 11:12 */   public double speed = 0.0D;
/* 12:   */   
/* 13:   */   public class View
/* 14:   */     extends MaterialEntity.View
/* 15:   */   {
/* 16:   */     public View()
/* 17:   */     {
/* 18:17 */       super();
/* 19:   */     }
/* 20:   */     
/* 21:   */     public double speed()
/* 22:   */     {
/* 23:22 */       if (MovingEntity.this.isAiObject) {
/* 24:23 */         throw new Error("Cannot access to this function");
/* 25:   */       }
/* 26:24 */       return MovingEntity.this.speed;
/* 27:   */     }
/* 28:   */     
/* 29:   */     Coord.View inertia()
/* 30:   */     {
/* 31:31 */       if (MovingEntity.this.isAiObject) {
/* 32:32 */         throw new Error("Cannot access to this function");
/* 33:   */       }
/* 34:33 */       return MovingEntity.this.inertia.view();
/* 35:   */     }
/* 36:   */   }
/* 37:   */   
/* 38:   */   public MovingEntity(int id, Unique<Coord> pos, Unique<Coord> ine)
/* 39:   */   {
/* 40:38 */     super(id);
/* 41:39 */     this.position = ((Coord)pos.take());
/* 42:40 */     this.inertia = ((Coord)ine.take());
/* 43:   */   }
/* 44:   */   
/* 45:   */   public MovingEntity(View src)
/* 46:   */   {
/* 47:44 */     super(src);
/* 48:   */     
/* 49:46 */     rotation(src.rotation());
/* 50:47 */     this.position = src.position().copied();
/* 51:48 */     this.speed = src.speed();
/* 52:49 */     this.inertia = src.inertia().copied();
/* 53:   */   }
/* 54:   */   
/* 55:   */   public Coord.View position()
/* 56:   */   {
/* 57:54 */     return this.position.view();
/* 58:   */   }
/* 59:   */   
/* 60:   */   public View view()
/* 61:   */   {
/* 62:58 */     return new View();
/* 63:   */   }
/* 64:   */   
/* 65:   */   public MovingEntity copy(Copyable.Context context)
/* 66:   */   {
/* 67:64 */     if (context.containsKey(this)) {
/* 68:64 */       return (MovingEntity)context.getSafe(this);
/* 69:   */     }
/* 70:65 */     MovingEntity ret = new MovingEntity(new View());
/* 71:66 */     context.putSafe(this, ret);
/* 72:67 */     return ret;
/* 73:   */   }
/* 74:   */   
/* 75:   */   public Unique<Coord> speedVector()
/* 76:   */   {
/* 77:74 */     return new Coord.Unique(Math.cos(rotation()) * this.speed, Math.sin(rotation()) * this.speed);
/* 78:   */   }
/* 79:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     model.MovingEntity
 * JD-Core Version:    0.7.0.1
 */