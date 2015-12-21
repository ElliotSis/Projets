/*   1:    */ package model;
/*   2:    */ 
/*   3:    */ import common.Copyable.Context;
/*   4:    */ import common.ListView;
/*   5:    */ import common.MapView;
/*   6:    */ import common.Unique;
/*   7:    */ import common.Util;
/*   8:    */ import common.Viewable;
/*   9:    */ import common.Viewable.View;
/*  10:    */ import java.util.LinkedHashMap;
/*  11:    */ import java.util.Map;
/*  12:    */ 
/*  13:    */ public class Country
/*  14:    */   extends AbstractBase
/*  15:    */   implements Viewable<View>
/*  16:    */ {
/*  17:    */   public final Map<Integer, Request> productionLine;
/*  18:    */   
/*  19:    */   public class View
/*  20:    */     extends AbstractBase.View
/*  21:    */   {
/*  22:    */     public View()
/*  23:    */     {
/*  24: 18 */       super();
/*  25:    */     }
/*  26:    */     
/*  27:    */     public ListView<Plane.FullView> planes()
/*  28:    */     {
/*  29: 24 */       return Util.view(Country.this.planes);
/*  30:    */     }
/*  31:    */     
/*  32:    */     Country copied(Copyable.Context context)
/*  33:    */     {
/*  34: 29 */       return Country.this.copy(context);
/*  35:    */     }
/*  36:    */     
/*  37:    */     public MapView<Integer, Country.Request.View> productionLine()
/*  38:    */     {
/*  39: 34 */       return Util.view(Country.this.productionLine);
/*  40:    */     }
/*  41:    */     
/*  42:    */     public String toString()
/*  43:    */     {
/*  44: 39 */       return "id: " + id();
/*  45:    */     }
/*  46:    */   }
/*  47:    */   
/*  48:    */   public class Request
/*  49:    */     implements Viewable<View>
/*  50:    */   {
/*  51:    */     public final int rqId;
/*  52:    */     public double timeBeforePlaneBuilt;
/*  53:    */     public Plane.Type requestedType;
/*  54:    */     
/*  55:    */     public Request(int requestId, double time, Plane.Type ptype)
/*  56:    */     {
/*  57: 53 */       this.rqId = requestId;
/*  58: 54 */       this.timeBeforePlaneBuilt = time;
/*  59: 55 */       ptype = this.requestedType;
/*  60:    */     }
/*  61:    */     
/*  62:    */     public class View
/*  63:    */       implements Viewable.View
/*  64:    */     {
/*  65:    */       public View() {}
/*  66:    */       
/*  67:    */       public int rqId()
/*  68:    */       {
/*  69: 65 */         return Country.Request.this.rqId;
/*  70:    */       }
/*  71:    */       
/*  72:    */       public double timeBeforePlaneBuilt()
/*  73:    */       {
/*  74: 69 */         return timeBeforePlaneBuilt();
/*  75:    */       }
/*  76:    */       
/*  77:    */       public Plane.Type requestedType()
/*  78:    */       {
/*  79: 74 */         return Country.Request.this.requestedType;
/*  80:    */       }
/*  81:    */     }
/*  82:    */     
/*  83:    */     public View view()
/*  84:    */     {
/*  85: 80 */       return new View();
/*  86:    */     }
/*  87:    */   }
/*  88:    */   
/*  89:    */   public Country(int id, Unique<Coord> pos)
/*  90:    */   {
/*  91: 87 */     super(id, pos);
/*  92: 88 */     this.productionLine = new LinkedHashMap();
/*  93:    */   }
/*  94:    */   
/*  95:    */   public Country(View src, Copyable.Context context)
/*  96:    */   {
/*  97: 92 */     super(src, context);
/*  98: 93 */     this.productionLine = new LinkedHashMap();
/*  99:    */   }
/* 100:    */   
/* 101:    */   public Country copy(Copyable.Context context)
/* 102:    */   {
/* 103: 98 */     if (context.containsKey(this)) {
/* 104: 99 */       return (Country)context.getSafe(this);
/* 105:    */     }
/* 106:100 */     Country c = new Country(view(), context);
/* 107:101 */     return c;
/* 108:    */   }
/* 109:    */   
/* 110:    */   public View view()
/* 111:    */   {
/* 112:106 */     return new View();
/* 113:    */   }
/* 114:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     model.Country
 * JD-Core Version:    0.7.0.1
 */