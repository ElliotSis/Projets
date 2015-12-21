/*   1:    */ package model;
/*   2:    */ 
/*   3:    */ import common.Copyable.Context;
/*   4:    */ import common.ListView;
/*   5:    */ import common.SetView;
/*   6:    */ import common.Unique;
/*   7:    */ import common.Util;
/*   8:    */ import common.Viewable;
/*   9:    */ import java.io.Serializable;
/*  10:    */ import java.util.HashSet;
/*  11:    */ import java.util.List;
/*  12:    */ import java.util.Set;
/*  13:    */ 
/*  14:    */ public class Base
/*  15:    */   extends AbstractBase
/*  16:    */   implements Serializable, Viewable<FullView>
/*  17:    */ {
/*  18:    */   private static final long serialVersionUID = 1L;
/*  19:    */   public final Set<ProgressAxis.Oriented> axes;
/*  20:    */   private static final double DEFAULT_BASE_RADAR_RANGE = 0.7D;
/*  21:    */   public double militaryGarrison;
/*  22:    */   public double fuelInStock;
/*  23: 28 */   public boolean fullViewInSync = true;
/*  24:    */   public final FullView fullView;
/*  25:    */   public final BasicView basicView;
/*  26:    */   
/*  27:    */   public class FullView
/*  28:    */     extends Base.BasicView
/*  29:    */   {
/*  30:    */     public FullView()
/*  31:    */     {
/*  32: 36 */       super();
/*  33:    */     }
/*  34:    */     
/*  35:    */     private FullView(boolean ignoreSync)
/*  36:    */     {
/*  37: 37 */       super();this.ignoreSync = ignoreSync;
/*  38:    */     }
/*  39:    */     
/*  40:    */     public boolean inSync()
/*  41:    */     {
/*  42: 39 */       return Base.this.fullViewInSync;
/*  43:    */     }
/*  44:    */     
/*  45:    */     protected String outOfSyncMsg()
/*  46:    */     {
/*  47: 43 */       return "This base can no longer be fully viewed (perhaps it's not yours anymore). Use method asLastViewed for an outdated view.";
/*  48:    */     }
/*  49:    */     
/*  50:    */     public FullView asLastViewed()
/*  51:    */     {
/*  52: 50 */       return new FullView(Base.this, true);
/*  53:    */     }
/*  54:    */     
/*  55:    */     public ListView<Plane.FullView> planes()
/*  56:    */     {
/*  57: 57 */       return Util.view(Base.this.planes);
/*  58:    */     }
/*  59:    */     
/*  60:    */     public double militaryGarrison()
/*  61:    */     {
/*  62: 63 */       checkSynx(Base.this.fullViewInSync);return Base.this.militaryGarrison;
/*  63:    */     }
/*  64:    */     
/*  65:    */     public double fuelInStock()
/*  66:    */     {
/*  67: 68 */       checkSynx(Base.this.fullViewInSync);return Base.this.fuelInStock;
/*  68:    */     }
/*  69:    */     
/*  70:    */     public boolean canSee(MaterialEntity.View e)
/*  71:    */     {
/*  72: 76 */       checkSynx(Base.this.fullViewInSync);
/*  73: 77 */       if (((e instanceof Plane.FullView)) && 
/*  74: 78 */         (((Plane.FullView)e).state() == Plane.State.AT_AIRPORT) && 
/*  75: 79 */         (isFriend(e))) {
/*  76: 82 */         return planes().containsTypeSafe((Plane.FullView)e);
/*  77:    */       }
/*  78: 83 */       if ((e instanceof MaterialEntity.View)) {
/*  79: 84 */         return isWithinRadar(e.position);
/*  80:    */       }
/*  81: 85 */       return false;
/*  82:    */     }
/*  83:    */     
/*  84:    */     public boolean isWithinRadar(Coord.View pos)
/*  85:    */     {
/*  86: 94 */       checkSynx(Base.this.fullViewInSync);
/*  87: 95 */       return this.position.squareDistanceTo(pos) <= Base.this.radarRange * Base.this.radarRange;
/*  88:    */     }
/*  89:    */     
/*  90:    */     public boolean isInTerritory()
/*  91:    */     {
/*  92:102 */       checkSynx(Base.this.fullViewInSync);
/*  93:103 */       for (ProgressAxis.Oriented pao : Base.this.axes) {
/*  94:104 */         if (pao.next.ownerId() != ownerId()) {
/*  95:105 */           return false;
/*  96:    */         }
/*  97:    */       }
/*  98:106 */       return true;
/*  99:    */     }
/* 100:    */     
/* 101:    */     public boolean canExpand()
/* 102:    */     {
/* 103:113 */       checkSynx(Base.this.fullViewInSync);
/* 104:114 */       return Base.this.militaryGarrison > GameSettings.MINIMUM_BASE_GARRISON;
/* 105:    */     }
/* 106:    */     
/* 107:    */     public boolean canCapture()
/* 108:    */     {
/* 109:120 */       checkSynx(Base.this.fullViewInSync);
/* 110:121 */       return Base.this.militaryGarrison > GameSettings.MINIMUM_CAPTURE_GARRISON;
/* 111:    */     }
/* 112:    */     
/* 113:    */     public String toString()
/* 114:    */     {
/* 115:130 */       if (Base.this.fullViewInSync) {
/* 116:131 */         return "FullBaseView id: " + id() + " pos: " + position().toString() + " [out of sync]";
/* 117:    */       }
/* 118:132 */       return "FullBaseView id: " + id() + " pos: " + position().toString() + " fuel: " + fuelInStock() + " mil: " + militaryGarrison() + " owner: " + ownerId();
/* 119:    */     }
/* 120:    */   }
/* 121:    */   
/* 122:    */   public class BasicView
/* 123:    */     extends AbstractBase.View
/* 124:    */   {
/* 125:    */     public BasicView()
/* 126:    */     {
/* 127:140 */       super();
/* 128:    */     }
/* 129:    */     
/* 130:    */     public SetView<ProgressAxis.Oriented> axes()
/* 131:    */     {
/* 132:146 */       return Util.shallowView(Base.this.axes);
/* 133:    */     }
/* 134:    */     
/* 135:    */     Base copied(Copyable.Context context)
/* 136:    */     {
/* 137:151 */       return Base.this.copy(context);
/* 138:    */     }
/* 139:    */   }
/* 140:    */   
/* 141:    */   @Deprecated
/* 142:    */   public void capture(int newId)
/* 143:    */   {
/* 144:163 */     if (ownerId() != newId)
/* 145:    */     {
/* 146:164 */       this.militaryGarrison = 0.0D;
/* 147:167 */       for (ProgressAxis.Oriented arc : this.axes) {
/* 148:169 */         arc.ratio(0.0D);
/* 149:    */       }
/* 150:    */     }
/* 151:179 */     ownerId(newId);
/* 152:    */   }
/* 153:    */   
/* 154:    */   public void resetAxes()
/* 155:    */   {
/* 156:182 */     for (ProgressAxis.Oriented arc : this.axes) {
/* 157:183 */       arc.ratio(0.0D);
/* 158:    */     }
/* 159:    */   }
/* 160:    */   
/* 161:    */   public FullView view()
/* 162:    */   {
/* 163:189 */     return this.fullView;
/* 164:    */   }
/* 165:    */   
/* 166:    */   public BasicView restrictedView()
/* 167:    */   {
/* 168:194 */     return this.basicView;
/* 169:    */   }
/* 170:    */   
/* 171:    */   public Base(int id, Unique<Coord> pos)
/* 172:    */   {
/* 173:198 */     super(id, pos);
/* 174:199 */     this.axes = new HashSet();
/* 175:200 */     this.radarRange = 0.7D;
/* 176:201 */     this.fuelInStock = 0.0D;
/* 177:202 */     this.militaryGarrison = 0.0D;
/* 178:    */     
/* 179:204 */     this.fullView = new FullView();
/* 180:205 */     this.basicView = new BasicView();
/* 181:    */   }
/* 182:    */   
/* 183:    */   public Base(FullView src, Copyable.Context context)
/* 184:    */   {
/* 185:209 */     super(src, context);
/* 186:210 */     context.putSafe(src.model(), this);
/* 187:213 */     for (Plane.FullView p : src.planes()) {
/* 188:215 */       this.planes.add(p.copied(context));
/* 189:    */     }
/* 190:216 */     this.axes = new HashSet();
/* 191:217 */     this.radarRange = 0.7D;
/* 192:218 */     for (ProgressAxis.Oriented oa : src.axes()) {
/* 193:220 */       this.axes.add(oa.copy(context));
/* 194:    */     }
/* 195:222 */     this.militaryGarrison = src.militaryGarrison();
/* 196:223 */     this.fuelInStock = src.fuelInStock();
/* 197:    */     
/* 198:225 */     this.fullView = new FullView();
/* 199:226 */     this.basicView = new BasicView();
/* 200:    */   }
/* 201:    */   
/* 202:    */   public Base copy(Copyable.Context context)
/* 203:    */   {
/* 204:231 */     if (context.containsKey(this)) {
/* 205:232 */       return (Base)context.getSafe(this);
/* 206:    */     }
/* 207:233 */     Base ret = new Base(view(), context);
/* 208:234 */     return ret;
/* 209:    */   }
/* 210:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     model.Base
 * JD-Core Version:    0.7.0.1
 */