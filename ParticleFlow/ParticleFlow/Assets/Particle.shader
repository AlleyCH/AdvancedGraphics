Shader "Custom/Particle" {
    Properties{
        _PointSize("Point size", Float) = 5.0
    }

        SubShader{
            Pass {
                Tags{ "RenderType" = "Opaque" }
                LOD 200
                Blend SrcAlpha one

                CGPROGRAM
                #pragma vertex vert
                #pragma fragment frag
                #include "UnityCG.cginc"

                uniform float _PointSize;

                #pragma target 5.0

                struct Particle {
                    float3 position;
                    float3 velocity;
                    float life;
                };

                StructuredBuffer<Particle> particleBuffer;

                struct v2f {
                    float4 position : SV_POSITION;
                    float4 color : COLOR;
                    float life : LIFE;
                    float size : PSIZE;
                };

                v2f vert(uint vertex_id : SV_VertexID, uint instance_id : SV_InstanceID) {
                    v2f o = (v2f)0;
                    float spread_factor = 3;
                    o.position = UnityObjectToClipPos(float4(particleBuffer[instance_id].position * spread_factor, 1));
                    o.size = 1;
                    return o;
                }

                float4 frag(v2f i) : COLOR {
                    return float4(0, 1, 0, 1);
                }
                ENDCG
            }
    }
        FallBack Off
}
