
struct VertexInput
{
	float4 position : POSITION0; //용도
    float4 color : COLOR0;
};
// PI
struct PixelInput
{
    float4 position : SV_POSITION; //화면좌표계 포지션
    float4 color : COLOR0;
};

//오브젝트의 크기 회전 이동
cbuffer VS_WVP : register(b0) //register(b0)
{
    matrix WVP;
}
cbuffer VS_COLOR : register(b1)
{
    //4 개의 4바이트
    float4 color;
}



PixelInput VS(VertexInput input)
{
    //공간변환이 있을 예정인 곳
    PixelInput output;
    
    output.position = mul(input.position, WVP);
	output.color = input.color + (color * 2.0f - 1.0f);
	saturate(output.color);
    
	return output;
}
//->pixel  PS   ->color
//픽셀쉐이더 진입 함수
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET 은 타겟이될 색깔 
{
    //뷰포트까지 변환이 끝났을때
    //스크린좌표
    
	float4 OutputColor;
	OutputColor = saturate(input.color);
    
	return OutputColor;
}