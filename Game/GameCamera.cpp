#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#define _USE_MATH_DEFINES //M_PI �~�����Ăяo��
#include <math.h> 
GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}
bool GameCamera::Start()
{
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("Player");
	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	//�j�A�N���b�v�ƃt�@�[�N���b�v�̊Ԃ��J�����̉f���͈͂ɂȂ�
	MainCamera().SetNear(1.0f);     //�j�A�N���b�v�@�J��������߂��ق��̖�
	MainCamera().SetFar(45000.0f);  //�t�@�[�N���b�v�@�J�������牓���ق��̖�
	return true;
}
void GameCamera::Update()
{
	m_playerposition = m_player->GetPosition();
	CVector3 stickR;
	stickR.x = -Pad(0).GetRStickXF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
	stickR.y = Pad(0).GetRStickYF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
	stickR.z = 0.0f;
	//�E�X�e�B�b�N�̓���
	//�E�X�e�B�b�N
	m_sdegreexz = -stickR.x * 2.0f;
	m_sdegreey = -stickR.y*2.0f;

	//��]�x���Z
	m_degreexz += m_sdegreexz;
	m_degreey += m_sdegreey;
	//�㉺�����̃J�����ړ��𐧌�
	if (m_degreey >= 70.0f) {
		m_degreey = 70.0f;
	}
	if (m_degreey <= -15.0f) {
		m_degreey = -15.0f;
	}
	//�p�x�����W�A���P�ʂɒ���
	m_radianx = M_PI / 180 * m_degreexz;
	m_radiany = M_PI / 180 * m_degreey;
	Hutu();
	//���_
	MainCamera().SetTarget(m_target);
	//���W
	MainCamera().SetPosition(m_position);
	//�J�����̍X�V�B
	MainCamera().Update();
}
// ���ʎ��_�̏��� �J�����̍��W���ړ�������A�J�����̒����_�����Z�b�g
void GameCamera::Hutu()
{
	m_target = { 0.0f,0.0f,0.0f };
	m_target.y += 140.0f;
	m_target += m_player->GetPosition();
	//�����_���v�Z����B
	//target.y += 200.0f;
	//Y������ɉ�]������B
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, m_radianx);
	m_toPos = { 0.0f, 0.0f, 1.0f };
	qRot.Multiply(m_toPos);
	//�㉺�̉�]�B
	//�܂��͉񂷎����v�Z����B
	CVector3 rotAxis;
	rotAxis.Cross(m_toPos, CVector3::AxisY);
	//�x�N�g���𐳋K������B
	rotAxis.Normalize();
	qRot.SetRotation(rotAxis, m_radiany);
	qRot.Multiply(m_toPos);
	m_toPos *= m_r;
	m_position = m_target + m_toPos * 2.0f;

	/*ps = toPos / r;
	CVector3 rotAxis3;
	rotAxis3.Cross(toPos, CVector3::AxisY);
	rotAxis3.Normalize();
	rotAxis3.y -= rotAxis3.y;
	ps = rotAxis3;*/

	m_toPos *= 4;
	//m_toPos.y = 0.0f;
	m_target -= m_toPos;
	m_toPos *= 1.5f;
	/*toPos.x = -r * cos(radianx);
	toPos.y = r * sin(radiany);
	toPos.z=r*(sin(radianx)+cos(radiany));*/
	//toPos.z = r * sin(radianx);
}