/*  1:   */ package common;
/*  2:   */ 
/*  3:   */ import model.Coord.Unique;
/*  4:   */ 
/*  5:   */ public class CoordConverter
/*  6:   */ {
/*  7:   */   private double min_long;
/*  8:   */   private double max_long;
/*  9:   */   private double min_lat;
/* 10:   */   private double max_lat;
/* 11:   */   private double latAmplitude;
/* 12:   */   private double longAmplitude;
/* 13:   */   private double widthWorld;
/* 14:   */   private double heightWorld;
/* 15:   */   
/* 16:   */   public CoordConverter(double minla, double maxla, double minlo, double maxlo, double zoom)
/* 17:   */   {
/* 18:24 */     this.min_lat = minla;
/* 19:25 */     this.max_lat = maxla;
/* 20:26 */     this.min_long = minlo;
/* 21:27 */     this.max_long = maxlo;
/* 22:   */     
/* 23:29 */     this.latAmplitude = (this.max_lat - this.min_lat);
/* 24:30 */     this.longAmplitude = (this.max_long - this.min_long);
/* 25:   */     
/* 26:32 */     this.widthWorld = (this.longAmplitude * zoom);
/* 27:33 */     this.heightWorld = (this.latAmplitude * zoom);
/* 28:   */   }
/* 29:   */   
/* 30:   */   public double getWidth()
/* 31:   */   {
/* 32:37 */     return this.widthWorld;
/* 33:   */   }
/* 34:   */   
/* 35:   */   public double getHeight()
/* 36:   */   {
/* 37:41 */     return this.heightWorld;
/* 38:   */   }
/* 39:   */   
/* 40:   */   public Coord.Unique toCartesianUnique(double longitude, double latitude)
/* 41:   */   {
/* 42:64 */     return new Coord.Unique((longitude - this.min_long) / this.longAmplitude * this.widthWorld, this.heightWorld - this.heightWorld * ((latitude - this.min_lat) / this.latAmplitude));
/* 43:   */   }
/* 44:   */   
/* 45:   */   public double getLatFromUnique(Coord.Unique coord)
/* 46:   */   {
/* 47:68 */     return (this.heightWorld - coord.y()) / this.heightWorld * this.latAmplitude + this.min_lat;
/* 48:   */   }
/* 49:   */   
/* 50:   */   public double getLatFromY(double y)
/* 51:   */   {
/* 52:72 */     return (this.heightWorld - y) / this.heightWorld * this.latAmplitude + this.min_lat;
/* 53:   */   }
/* 54:   */   
/* 55:   */   public double getLongFromUnique(Coord.Unique coord)
/* 56:   */   {
/* 57:76 */     return coord.x() / this.widthWorld * this.longAmplitude + this.min_long;
/* 58:   */   }
/* 59:   */   
/* 60:   */   public double getLongFromX(double x)
/* 61:   */   {
/* 62:80 */     return x / this.widthWorld * this.longAmplitude + this.min_long;
/* 63:   */   }
/* 64:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.CoordConverter
 * JD-Core Version:    0.7.0.1
 */