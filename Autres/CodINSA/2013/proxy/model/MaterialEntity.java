/*  1:   */ package model;
/*  2:   */ 
/*  3:   */ public abstract class MaterialEntity
/*  4:   */   extends Entity
/*  5:   */ {
/*  6:   */   private static final double DEFAULT_ENTITY_RADAR_RANGE = 0.0D;
/*  7:12 */   private double rotation = 0.0D;
/*  8:   */   protected double radarRange;
/*  9:   */   
/* 10:   */   public abstract Coord.View position();
/* 11:   */   
/* 12:   */   public MaterialEntity(int id)
/* 13:   */   {
/* 14:20 */     super(id);
/* 15:21 */     this.radarRange = 0.0D;
/* 16:   */   }
/* 17:   */   
/* 18:   */   public MaterialEntity(View src)
/* 19:   */   {
/* 20:24 */     super(src);
/* 21:   */     
/* 22:26 */     this.rotation = src.rotation();
/* 23:27 */     this.radarRange = src.radarRange();
/* 24:   */   }
/* 25:   */   
/* 26:   */   public class View
/* 27:   */     extends Entity.View
/* 28:   */   {
/* 29:   */     public View()
/* 30:   */     {
/* 31:30 */       super();
/* 32:   */     }
/* 33:   */     
/* 34:32 */     public final Coord.View position = MaterialEntity.this.position();
/* 35:   */     
/* 36:   */     public Coord.View position()
/* 37:   */     {
/* 38:36 */       return this.position;
/* 39:   */     }
/* 40:   */     
/* 41:   */     public double rotation()
/* 42:   */     {
/* 43:42 */       if (MaterialEntity.this.isAiObject) {
/* 44:43 */         throw new Error("Cannot access to this function");
/* 45:   */       }
/* 46:44 */       return MaterialEntity.this.rotation;
/* 47:   */     }
/* 48:   */     
/* 49:   */     public double radarRange()
/* 50:   */     {
/* 51:49 */       return MaterialEntity.this.radarRange;
/* 52:   */     }
/* 53:   */     
/* 54:   */     public boolean canSee(View e)
/* 55:   */     {
/* 56:56 */       return false;
/* 57:   */     }
/* 58:   */   }
/* 59:   */   
/* 60:   */   public double rotation()
/* 61:   */   {
/* 62:61 */     return this.rotation;
/* 63:   */   }
/* 64:   */   
/* 65:   */   public void rotation(double angle)
/* 66:   */   {
/* 67:64 */     this.rotation = angle;
/* 68:65 */     this.rotation %= 6.283185307179586D;
/* 69:66 */     if (this.rotation > 3.141592653589793D) {
/* 70:67 */       this.rotation -= 6.283185307179586D;
/* 71:   */     }
/* 72:   */   }
/* 73:   */   
/* 74:   */   public void rotate(double angle_delta)
/* 75:   */   {
/* 76:70 */     rotation(this.rotation + angle_delta);
/* 77:   */   }
/* 78:   */   
/* 79:   */   public View view()
/* 80:   */   {
/* 81:75 */     return new View();
/* 82:   */   }
/* 83:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     model.MaterialEntity
 * JD-Core Version:    0.7.0.1
 */