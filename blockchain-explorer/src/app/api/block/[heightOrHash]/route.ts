import { NextRequest, NextResponse } from 'next/server';
import { getBlock } from '@/lib/api';

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<{ heightOrHash: string }> }
) {
  try {
    const { heightOrHash } = await params;

    if (!heightOrHash) {
      return NextResponse.json(
        {
          success: false,
          error: 'Block height or hash is required',
        },
        { status: 400 }
      );
    }

    const block = await getBlock(heightOrHash);

    return NextResponse.json({
      success: true,
      data: block,
    });
  } catch (error) {
    console.error('API /block/[heightOrHash] error:', error);

    return NextResponse.json(
      {
        success: false,
        error: 'Block not found',
        message: error instanceof Error ? error.message : 'Unknown error',
      },
      { status: 404 }
    );
  }
}