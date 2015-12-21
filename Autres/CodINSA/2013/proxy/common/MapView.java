/*   1:    */ package common;
/*   2:    */ 
/*   3:    */ import java.util.AbstractMap;
/*   4:    */ import java.util.Collections;
/*   5:    */ import java.util.Map;
/*   6:    */ import java.util.Map.Entry;
/*   7:    */ import java.util.Set;
/*   8:    */ 
/*   9:    */ public abstract interface MapView<K, T>
/*  10:    */   extends Viewable.View
/*  11:    */ {
/*  12:    */   public abstract Map<K, T> asUnmodifiableMap();
/*  13:    */   
/*  14:    */   public abstract boolean containsKey(Object paramObject);
/*  15:    */   
/*  16:    */   public abstract boolean containsValue(Object paramObject);
/*  17:    */   
/*  18:    */   public abstract SetView<EntryView<K, T>> entrySetView();
/*  19:    */   
/*  20:    */   public abstract T get(Object paramObject);
/*  21:    */   
/*  22:    */   public abstract boolean isEmpty();
/*  23:    */   
/*  24:    */   public abstract SetView<K> keySetView();
/*  25:    */   
/*  26:    */   public abstract int size();
/*  27:    */   
/*  28:    */   public abstract CollectionView<T> valuesView();
/*  29:    */   
/*  30:    */   public static class ShallowOf<K, T>
/*  31:    */     extends AbstractMap<K, T>
/*  32:    */     implements MapView<K, T>
/*  33:    */   {
/*  34:    */     final Map<K, T> delegate;
/*  35:    */     
/*  36:    */     public ShallowOf(Map<K, T> src)
/*  37:    */     {
/*  38: 93 */       this.delegate = src;
/*  39:    */     }
/*  40:    */     
/*  41:    */     protected Map<K, T> delegate()
/*  42:    */     {
/*  43: 96 */       return this.delegate;
/*  44:    */     }
/*  45:    */     
/*  46:    */     public Map<K, T> asUnmodifiableMap()
/*  47:    */     {
/*  48:100 */       return Collections.unmodifiableMap(this.delegate);
/*  49:    */     }
/*  50:    */     
/*  51:    */     public Set<Map.Entry<K, T>> entrySet()
/*  52:    */     {
/*  53:105 */       return asUnmodifiableMap().entrySet();
/*  54:    */     }
/*  55:    */     
/*  56:    */     public SetView<MapView.EntryView<K, T>> entrySetView()
/*  57:    */     {
/*  58:109 */       new SetView.Transform(this.delegate.entrySet(), new Util.Converter()
/*  59:    */       {
/*  60:    */         public MapView.EntryView<K, T> convert(Map.Entry<K, T> src)
/*  61:    */         {
/*  62:111 */           return Helper.makeEntryView(src);
/*  63:    */         }
/*  64:    */       });
/*  65:    */     }
/*  66:    */     
/*  67:    */     public SetView<K> keySetView()
/*  68:    */     {
/*  69:117 */       return new SetView.ShallowOf(this.delegate.keySet());
/*  70:    */     }
/*  71:    */     
/*  72:    */     public CollectionView<T> valuesView()
/*  73:    */     {
/*  74:121 */       return new CollectionView.ShallowOf(this.delegate.values());
/*  75:    */     }
/*  76:    */   }
/*  77:    */   
/*  78:    */   public static class Transform<K, U>
/*  79:    */     extends AbstractMap<K, U>
/*  80:    */     implements MapView<K, U>
/*  81:    */   {
/*  82:    */     final Map<K, Object> delegate;
/*  83:    */     final Util.Converter<Object, U> transformer;
/*  84:    */     
/*  85:    */     public <T> Transform(Map<K, T> src, Util.Converter<T, U> transformer)
/*  86:    */     {
/*  87:137 */       this.delegate = src;
/*  88:138 */       this.transformer = transformer;
/*  89:    */     }
/*  90:    */     
/*  91:    */     public Map<K, U> asUnmodifiableMap()
/*  92:    */     {
/*  93:143 */       return this;
/*  94:    */     }
/*  95:    */     
/*  96:    */     public Set<Map.Entry<K, U>> entrySet()
/*  97:    */     {
/*  98:176 */       new SetView.Transform(this.delegate.entrySet(), new Util.Converter()
/*  99:    */       {
/* 100:    */         public Map.Entry<K, U> convert(final Map.Entry<K, Object> src)
/* 101:    */         {
/* 102:178 */           new Map.Entry()
/* 103:    */           {
/* 104:    */             public K getKey()
/* 105:    */             {
/* 106:180 */               return src.getKey();
/* 107:    */             }
/* 108:    */             
/* 109:    */             public U getValue()
/* 110:    */             {
/* 111:183 */               return MapView.Transform.this.transformer.convert(src.getValue());
/* 112:    */             }
/* 113:    */             
/* 114:    */             public U setValue(U arg0)
/* 115:    */             {
/* 116:186 */               throw new UnsupportedOperationException();
/* 117:    */             }
/* 118:    */           };
/* 119:    */         }
/* 120:    */       });
/* 121:    */     }
/* 122:    */     
/* 123:    */     public SetView<MapView.EntryView<K, U>> entrySetView()
/* 124:    */     {
/* 125:197 */       new SetView.Transform(this.delegate.entrySet(), new Util.Converter()
/* 126:    */       {
/* 127:    */         public MapView.EntryView<K, U> convert(final Map.Entry<K, Object> src)
/* 128:    */         {
/* 129:199 */           new MapView.EntryView()
/* 130:    */           {
/* 131:    */             public K getKey()
/* 132:    */             {
/* 133:201 */               return src.getKey();
/* 134:    */             }
/* 135:    */             
/* 136:    */             public U getValue()
/* 137:    */             {
/* 138:204 */               return MapView.Transform.this.transformer.convert(src.getValue());
/* 139:    */             }
/* 140:    */           };
/* 141:    */         }
/* 142:    */       });
/* 143:    */     }
/* 144:    */     
/* 145:    */     public SetView<K> keySetView()
/* 146:    */     {
/* 147:213 */       return new SetView.ShallowOf(keySet());
/* 148:    */     }
/* 149:    */     
/* 150:    */     public CollectionView<U> valuesView()
/* 151:    */     {
/* 152:218 */       return new CollectionView.ShallowOf(values());
/* 153:    */     }
/* 154:    */   }
/* 155:    */   
/* 156:    */   public static class Of<K, V extends Viewable.View>
/* 157:    */     extends MapView.Transform<K, V>
/* 158:    */   {
/* 159:    */     public <T extends Viewable<V>> Of(Map<K, T> src)
/* 160:    */     {
/* 161:230 */       super(Util.getViewer());
/* 162:    */     }
/* 163:    */   }
/* 164:    */   
/* 165:    */   public static abstract interface EntryView<K, T>
/* 166:    */   {
/* 167:    */     public abstract K getKey();
/* 168:    */     
/* 169:    */     public abstract T getValue();
/* 170:    */   }
/* 171:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.MapView
 * JD-Core Version:    0.7.0.1
 */