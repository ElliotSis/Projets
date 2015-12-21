/*   1:    */ package model;
/*   2:    */ 
/*   3:    */ class InternalView
/*   4:    */ {
/*   5:    */   protected Coord model;
/*   6:    */   
/*   7:    */   public double x()
/*   8:    */   {
/*   9:369 */     return this.model.x;
/*  10:    */   }
/*  11:    */   
/*  12:    */   public double y()
/*  13:    */   {
/*  14:370 */     return this.model.y;
/*  15:    */   }
/*  16:    */   
/*  17:    */   public double norm()
/*  18:    */   {
/*  19:372 */     return Math.sqrt(this.model.x * this.model.x + this.model.y * this.model.y);
/*  20:    */   }
/*  21:    */   
/*  22:    */   public final Coord opposite()
/*  23:    */   {
/*  24:375 */     Coord r = new Coord(-this.model.x, -this.model.y);return r;
/*  25:    */   }
/*  26:    */   
/*  27:    */   public final double dot(Coord.View cv)
/*  28:    */   {
/*  29:378 */     return this.model.x * cv.x() + this.model.y * cv.y();
/*  30:    */   }
/*  31:    */   
/*  32:    */   public final Coord projectedOn(Coord.View cv)
/*  33:    */   {
/*  34:389 */     double n = cv.norm();
/*  35:390 */     return cv.multipliedBy(this.model.dot(cv) / (n * n));
/*  36:    */   }
/*  37:    */   
/*  38:    */   public final Coord addedTo(Coord.View cv)
/*  39:    */   {
/*  40:394 */     Coord r = new Coord(this.model);r.add(cv);return r;
/*  41:    */   }
/*  42:    */   
/*  43:    */   public final Coord addedTo(Coord.View cv, double coeff)
/*  44:    */   {
/*  45:397 */     Coord r = new Coord(this.model);r.shift(cv.x() * coeff, cv.y() * coeff);return r;
/*  46:    */   }
/*  47:    */   
/*  48:    */   public final Coord multipliedBy(double coeff)
/*  49:    */   {
/*  50:400 */     Coord r = new Coord(this.model);r.mult(coeff);return r;
/*  51:    */   }
/*  52:    */   
/*  53:    */   public final Coord shifted(double dx, double dy)
/*  54:    */   {
/*  55:403 */     Coord r = new Coord(this.model);r.shift(dx, dy);return r;
/*  56:    */   }
/*  57:    */   
/*  58:    */   public final Coord shifted(double shift)
/*  59:    */   {
/*  60:406 */     Coord r = new Coord(this.model);r.shift(shift);return r;
/*  61:    */   }
/*  62:    */   
/*  63:    */   public final Coord rotated(Coord.View center, double angle)
/*  64:    */   {
/*  65:409 */     Coord r = new Coord(this.model);r.rotate(center, angle);return r;
/*  66:    */   }
/*  67:    */   
/*  68:    */   public final double distanceTo(Coord.View cv)
/*  69:    */   {
/*  70:412 */     return Math.sqrt((cv.x() - this.model.x) * (cv.x() - this.model.x) + (cv.y() - this.model.y) * (cv.y() - this.model.y));
/*  71:    */   }
/*  72:    */   
/*  73:    */   public final double squareDistanceTo(Coord.View cv)
/*  74:    */   {
/*  75:415 */     return (cv.x() - this.model.x) * (cv.x() - this.model.x) + (cv.y() - this.model.y) * (cv.y() - this.model.y);
/*  76:    */   }
/*  77:    */   
/*  78:    */   public final double angleWith(Coord.View cv)
/*  79:    */   {
/*  80:418 */     return Math.atan2(cv.y() - this.model.y, cv.x() - this.model.x);
/*  81:    */   }
/*  82:    */   
/*  83:    */   public Coord copied()
/*  84:    */   {
/*  85:422 */     return this.model.copy(null);
/*  86:    */   }
/*  87:    */   
/*  88:    */   public boolean equals(Object e)
/*  89:    */   {
/*  90:426 */     if (e == null) {
/*  91:427 */       return false;
/*  92:    */     }
/*  93:428 */     if ((e instanceof Coord)) {
/*  94:429 */       return (this.model.x == ((Coord)e).x) && (this.model.y == ((Coord)e).y);
/*  95:    */     }
/*  96:430 */     if ((e instanceof Coord.View)) {
/*  97:431 */       return (this.model.x == ((Coord.View)e).x()) && (this.model.y == ((Coord.View)e).y());
/*  98:    */     }
/*  99:432 */     return false;
/* 100:    */   }
/* 101:    */   
/* 102:    */   public int hashCode()
/* 103:    */   {
/* 104:438 */     return Double.valueOf(this.model.x).hashCode() * 31 + Double.valueOf(this.model.y).hashCode();
/* 105:    */   }
/* 106:    */   
/* 107:    */   public String toString()
/* 108:    */   {
/* 109:444 */     return "Coord(" + this.model.x + ", " + this.model.y + ")";
/* 110:    */   }
/* 111:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     model.InternalView
 * JD-Core Version:    0.7.0.1
 */